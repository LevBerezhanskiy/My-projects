const dateFilter = document.getElementById("date");
const categoryFilter = document.getElementById("category");
const typeFilter = document.getElementById("type");
const transactionsTableBody = document.getElementById("transactionsTableBody");
const totalBalanceElement = document.getElementById("total-balance");

let allTransactions = []; // Тут храним все загруженные транзакции
let pollingIntervalId = null; // Для остановки автообновления, если нужно
const POLLING_INTERVAL_MS = 5000; // Как часто проверять обновления (5 секунд)

// Эта функция рисует таблицу на основе массива транзакций
function renderTransactions(transactionsToRender) {
    transactionsTableBody.innerHTML = ""; // Чистим старую таблицу
    let total = 0;

    if (transactionsToRender.length === 0) {
        transactionsTableBody.innerHTML = `<tr><td colspan="6">Транзакций нет.</td></tr>`;
    } else {
        transactionsToRender.forEach((t, index) => {
            const row = document.createElement("tr");

            // Берем данные из объекта транзакции
            const type = t.type || '';
            const category = t.category || '';
            const originalDate = t.date || ''; // YYYY-MM-DD
            const amount = parseFloat(t.amount) || 0; // Превращаем строку в число
            const description = t.description || '';

            // Форматируем дату в DD.MM.YYYY
            let displayDate = originalDate;
            if (originalDate.includes('-')) {
                const parts = originalDate.split('-');
                if (parts.length === 3) displayDate = `${parts[2]}.${parts[1]}.${parts[0]}`;
            }

            // Переводим тип на русский
            let displayType = type;
            if (type.toLowerCase() === 'income') displayType = 'Доход';
            else if (type.toLowerCase() === 'expense') displayType = 'Расход';

            // Заполняем строку таблицы
            row.innerHTML = `
                <td>${index + 1}</td>
                <td>${displayType}</td>
                <td>${category}</td>
                <td>${displayDate}</td>
                <td>${amount.toFixed(2)}</td>
                <td>${description}</td>
            `;
            transactionsTableBody.appendChild(row);

            // Считаем баланс
            total += (type === "income" ? amount : -amount);
        });
    }
    // Показываем итоговый баланс
    totalBalanceElement.textContent = total.toFixed(2);
}

// Эта функция фильтрует массив allTransactions по значениям в полях ввода
function applyFilters() {
    const selectedDate = dateFilter.value;
    const selectedCategory = categoryFilter.value.toLowerCase();
    const selectedType = typeFilter.value;

    const filtered = allTransactions.filter(t => {
        const dateMatch = !selectedDate || (t.date === selectedDate);
        const categoryMatch = !selectedCategory || (t.category || '').toLowerCase().includes(selectedCategory);
        const typeMatch = selectedType === "all" || (t.type === selectedType);
        return dateMatch && categoryMatch && typeMatch;
    });

    renderTransactions(filtered); // Перерисовываем таблицу с отфильтрованными данными
}

function fetchAndUpdateTransactions() {
    fetch("http://localhost:8080/transactions")
        .then(response => {
            if (!response.ok) {
                throw new Error(`HTTP error ${response.status}`);
            }
            return response.json();
        })
        .then(newData => {
            if (!Array.isArray(newData)) {
                throw new Error("Data is not an array");
            }
            if (JSON.stringify(allTransactions) !== JSON.stringify(newData)) {
                console.log("Data updated from server.");
                allTransactions = newData;
                applyFilters(); // Перерисовываем таблицу
            }
        })
        .catch(error => {
            console.error("Failed to fetch updates:", error);
            transactionsTableBody.innerHTML = '<tr><td colspan="6">Ошибка загрузки данных: ' + error.message + '</td></tr>';
        });
}

// Запускает периодический опрос сервера
function startPolling() {
    if (pollingIntervalId === null) {
        // console.log("Starting polling...");
        fetchAndUpdateTransactions(); // Проверяем сразу
        pollingIntervalId = setInterval(fetchAndUpdateTransactions, POLLING_INTERVAL_MS);
    }
}

document.addEventListener("DOMContentLoaded", () => {
    // 1. Добавляем слушатели на изменение фильтров
    dateFilter.addEventListener("change", applyFilters);
    categoryFilter.addEventListener("input", applyFilters);
    typeFilter.addEventListener("change", applyFilters);

    // 2. Загружаем данные первый раз и запускаем автообновление
    fetchAndUpdateTransactions(); // Первая загрузка
    startPolling(); // Запуск автообновления
});