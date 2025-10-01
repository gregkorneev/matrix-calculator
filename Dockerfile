# -------- Stage 1: build --------
FROM ubuntu:22.04 AS builder

# Базовые инструменты: cmake, компилятор и git
RUN apt-get update && \
    apt-get install -y cmake g++ git && \
    rm -rf /var/lib/apt/lists/*

# Корневая папка проекта внутри контейнера
WORKDIR /app

# Копируем весь проект (CMakeLists.txt, src/, include/, tests/, и т.п.)
COPY . .

# Чистая конфигурация и сборка
# Здесь же соберётся googletest через FetchContent (интернет нужен)
RUN rm -rf build && \
    cmake -B build && \
    cmake --build build --target matrix_calculator

# (Необязательно) Если хочешь проверить тесты прямо в образе:
# RUN cmake --build build --target matrix_tests && \
#     ctest --test-dir build --output-on-failure -V


# -------- Stage 2: runtime --------
FROM ubuntu:22.04
WORKDIR /app

# Копируем только готовый бинарник
COPY --from=builder /app/build/matrix_calculator .

# Точка входа — запуск приложения
CMD ["./matrix_calculator"]
