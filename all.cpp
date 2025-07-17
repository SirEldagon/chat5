#include <fstream>
#include <string>
#include <mutex>
#include <iostream>

class Logger {
public:
    // Конструктор: открывает файл для записи
    explicit Logger(const std::string& filename = "log.txt") : log_file(filename, std::ios::app) {
        if (!log_file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл логов");
        }
    }

    // Деструктор: закрывает файл
    ~Logger() {
        if (log_file.is_open()) {
            log_file.close();
        }
    }

    // Запись строки в лог
    void write(const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        log_file << message << std::endl;
    }

    // Чтение одной строки из файла
    std::string readLine() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!log_file.is_open()) {
            throw std::runtime_error("Файл закрыт");
        }

        // Перемещаемся в текущую позицию файла
        // и читаем строку
        std::string line;
        if (std::getline(log_file, line)) {
            return line;
        } else {
            return ""; // или можно выбросить исключение, если нужно
        }
    }

private:
    std::ofstream log_file;
    std::mutex mutex_;
};
