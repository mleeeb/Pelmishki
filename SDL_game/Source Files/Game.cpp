/**
 * @file Game.cpp
 * @brief Реализация методов класса Game.
 *
 * Этот файл содержит реализацию всех методов класса Game,
 * включая инициализацию, главный игровой цикл, обработку событий,
 * управление врагами, отрисовку и логику победы.
 */

#include "Game.h"
#include <iostream>

/**
 * @brief Конструктор класса Game.
 * 
 * Инициализирует все внутренние переменные состояния игры значениями по умолчанию.
 * Устанавливает прямоугольник отрисовки фона на весь экран.
 * Игра начинается в активном состоянии без экрана победы.
 */
Game::Game()
{
    mainrect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    gameActive = true;
    victoryScreen = false;
    victoryTexture = nullptr;
    currentEnemyIndex = 0;
    backgroundTexture = nullptr;
}

/**
 * @brief Деструктор класса Game.
 * 
 * Освобождает всю выделенную память: удаляет всех врагов из вектора,
 * уничтожает текстуру победы и текстуру фона.
 */
Game::~Game()
{
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    if (victoryTexture) {
        SDL_DestroyTexture(victoryTexture);
    }
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
    }
}

/**
 * @brief Инициализирует все подсистемы SDL и загружает ресурсы.
 * 
 * Выполняет последовательную инициализацию:
 * - Запускает SDL_Video и SDL_ttf
 * - Создаёт окно размером 540x720 с рендерером
 * - Пытается загрузить шрифт из нескольких возможных путей
 * - Создаёт градиентный фон
 * - Создаёт всех врагов для игры
 * 
 * @return SDL_APP_CONTINUE при успешной инициализации,
 *         SDL_APP_FAILURE если шрифт не удалось загрузить ни из одного пути.
 */
SDL_AppResult Game::SDL_AppInit()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    // Создаём окно 540x720
    SDL_CreateWindowAndRenderer("Clicker Game - Defeat All Enemies!",
        SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

    // Пробуем разные пути к шрифту
    const char* fontPaths[] = {
        "assets/Fonts/Font_HTR.ttf",
        "../SDL_game/Resourses/assets/Fonts/Font_HTR.ttf",
        "C:/Users/1991/source/repos/Pelmishki/SDL_game/Resourses/assets/Fonts/Font_HTR.ttf",
    };

    font = nullptr;
    for (int i = 0; i < 3; i++) {
        font = TTF_OpenFont(fontPaths[i], 36);  // Увеличенный размер шрифта
        if (font) {
            SDL_Log("Font loaded successfully from: %s", fontPaths[i]);
            break;
        }
        else {
            SDL_Log("Failed to load font from: %s", fontPaths[i]);
        }
    }

    if (!font) {
        SDL_Log("ERROR: Could not load font from any path!");
        return SDL_APP_FAILURE;
    }

    loadBackground();
    spawnEnemies();

    return SDL_APP_CONTINUE;
}

/**
 * @brief Создаёт всех врагов для текущей игры.
 * 
 * Очищает предыдущий список врагов, удаляя их из памяти.
 * Создаёт трёх врагов с возрастающими уровнем и здоровьем:
 * - Уровень 1: 30 HP, текстура "Stenka_derevyannaya2.jpg"
 * - Уровень 2: 40 HP, текстура "Stenka_kirpichnaya.jpg"
 * - Уровень 3: 50 HP, текстура "Seyf.jpg"
 * 
 * Если текстура не найдена, враг отображается цветным прямоугольником.
 * После создания всех врагов активируется первый из них.
 */
void Game::spawnEnemies() {
    // Очищаем старых врагов
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    // Враг на весь экран - размеры равны размеру окна
    // Позиция (0, 0) - левый верхний угол
    int x = 0;
    int y = 0;
    // Размер врага будет задан в конструкторе Enemy

    // Пути к изображениям для разных уровней
    const char* imagePaths[] = {
        "assets/Stenka_derevyannaya2.jpg",
        "assets/Stenka_kirpichnaya.jpg",
        "assets/Seyf.jpg"
    };

    // Создаём врагов
    for (int i = 0; i < 3; i++) {
        int health = 30 + i * 10;
        int level = i + 1;

        // Проверяем существование файла
        FILE* test = fopen(imagePaths[i], "rb");
        if (test) {
            fclose(test);
            SDL_Log("Found image: %s", imagePaths[i]);
            enemies.push_back(new Enemy(renderer, font, health, level, x, y, imagePaths[i]));
        }
        else {
            SDL_Log("Image NOT found: %s, using colored rectangle", imagePaths[i]);
            enemies.push_back(new Enemy(renderer, font, health, level, x, y, nullptr));
        }
    }

    gameActive = true;
    victoryScreen = false;
    currentEnemyIndex = 0;

    if (enemies.size() > 0) {
        enemies[0]->setActive(true);
        SDL_Log("Enemy 1 activated!");
    }
}

/**
 * @brief Активирует следующего врага в очереди.
 * 
 * Деактивирует текущего врага, увеличивает индекс currentEnemyIndex,
 * активирует следующего врага, если он существует.
 * Если врагов больше нет, вызывает checkVictory() для проверки победы.
 */
void Game::activateNextEnemy() {
    if (currentEnemyIndex < enemies.size()) {
        enemies[currentEnemyIndex]->setActive(false);
    }

    currentEnemyIndex++;

    if (currentEnemyIndex < enemies.size()) {
        enemies[currentEnemyIndex]->setActive(true);
        SDL_Log("Enemy %d activated!", currentEnemyIndex + 1);
    }
    else {
        checkVictory();
    }
}

/**
 * @brief Создаёт градиентный текстурный фон.
 * 
 * Создаёт текстуру-мишень размером с экран (540x720).
 * Заполняет её вертикальным градиентом от тёмно-сине-зелёного
 * к более светлому оттенку.
 * 
 * Градиент рассчитывается по формуле:
 * - Красный: от 20 до 50
 * - Зелёный: от 20 до 40
 * - Синий: от 40 до 80
 * 
 * @note В случае ошибки создания текстуры информация выводится в лог.
 */
void Game::loadBackground()
{
    backgroundTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (backgroundTexture) {
        SDL_Texture* oldTarget = SDL_GetRenderTarget(renderer);
        SDL_SetRenderTarget(renderer, backgroundTexture);

        // Рисуем градиент построчно
        for (int i = 0; i < SCREEN_HEIGHT; i++) {
            float t = i / (float)SCREEN_HEIGHT;
            Uint8 r = (Uint8)(20 + t * 30);
            Uint8 g = (Uint8)(20 + t * 20);
            Uint8 b = (Uint8)(40 + t * 40);
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_FRect rect = { 0, (float)i, (float)SCREEN_WIDTH, 1 };
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_SetRenderTarget(renderer, oldTarget);
        SDL_Log("Background texture created successfully");
    }
    else {
        SDL_Log("Failed to create background texture: %s", SDL_GetError());
    }
}

/**
 * @brief Обрабатывает входящие события SDL.
 * 
 * Реагирует на два типа событий:
 * - SDL_EVENT_QUIT: завершение работы приложения
 * - SDL_EVENT_MOUSE_BUTTON_DOWN: клик левой кнопкой мыши
 * 
 * При клике во время активной игры:
 * - Наносит урон текущему врагу (10 единиц)
 * - Проверяет, не погиб ли враг после удара
 * - Если враг погиб, активирует следующего
 * 
 * При клике на экране победы:
 * - Проверяет, что клик был по текстуре победы
 * - Вызывает resetGame() для перезапуска
 * 
 * @param event Указатель на событие SDL.
 * @return SDL_APP_SUCCESS если получен сигнал завершения,
 *         SDL_APP_CONTINUE в остальных случаях.
 */
SDL_AppResult Game::SDL_AppEvent(SDL_Event* event)
{
    switch (event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        if (event->button.button == SDL_BUTTON_LEFT) {
            float mouseX = event->button.x;
            float mouseY = event->button.y;

            if (victoryScreen) {
                if (isPointInRect(mouseX, mouseY, victoryRect)) {
                    resetGame();
                }
                break;
            }

            if (gameActive) {
                if (currentEnemyIndex < enemies.size() &&
                    enemies[currentEnemyIndex]->getActive() &&
                    enemies[currentEnemyIndex]->isAlive()) {
                    // Клик в любом месте экрана наносит урон (враг на весь экран)
                    enemies[currentEnemyIndex]->takeDamage(10);

                    SDL_Log("Hit enemy %d! Health left: %d/%d",
                        enemies[currentEnemyIndex]->getLevel(),
                        enemies[currentEnemyIndex]->getHealth(),
                        (currentEnemyIndex == 0 ? 30 : (currentEnemyIndex == 1 ? 40 : 50)));

                    if (!enemies[currentEnemyIndex]->isAlive()) {
                        SDL_Log("Enemy %d defeated!", currentEnemyIndex + 1);
                        activateNextEnemy();
                    }
                }
            }
        }
        break;
    }
    return SDL_APP_CONTINUE;
}

/**
 * @brief Проверяет, находится ли точка внутри прямоугольника.
 * 
 * Вспомогательный метод для проверки кликов по UI-элементам.
 * 
 * @param x Координата X точки (обычно позиция мыши).
 * @param y Координата Y точки.
 * @param rect Прямоугольник для проверки.
 * @return true если точка внутри прямоугольника, иначе false.
 */
bool Game::isPointInRect(float x, float y, SDL_FRect rect) {
    return (x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h);
}

/**
 * @brief Проверяет условия победы.
 * 
 * Если все враги побеждены (currentEnemyIndex >= enemies.size())
 * и игра ещё активна, устанавливает флаги gameActive = false
 * и victoryScreen = true, затем отображает экран победы.
 */
void Game::checkVictory() {
    if (currentEnemyIndex >= enemies.size() && gameActive) {
        gameActive = false;
        victoryScreen = true;
        showVictoryScreen();
    }
}

/**
 * @brief Создаёт текстурный экран победы.
 * 
 * Рендерит текст "VICTORY! Click to Play Again" золотым цветом (255, 215, 0).
 * Вычисляет размеры текста и позиционирует его по центру экрана.
 * 
 * @note Если создание поверхности не удалось, метод завершается без действий.
 */
void Game::showVictoryScreen() {
    std::string victoryText = "VICTORY! Click to Play Again";
    SDL_Color goldColor = { 255, 215, 0, 255 };

    SDL_Surface* surface = TTF_RenderText_Solid(font, victoryText.c_str(), (int)victoryText.length(), goldColor);
    if (!surface) return;

    victoryTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (victoryTexture) {
        SDL_GetTextureSize(victoryTexture, &victoryRect.w, &victoryRect.h);
        victoryRect.x = (SCREEN_WIDTH - victoryRect.w) / 2;
        victoryRect.y = (SCREEN_HEIGHT - victoryRect.h) / 2;
    }

    SDL_DestroySurface(surface);
}

/**
 * @brief Перезапускает игру.
 * 
 * Удаляет всех существующих врагов, освобождая память.
 * Очищает вектор enemies.
 * Уничтожает текстуру победы, если она существует.
 * Вызывает spawnEnemies() для создания новой игры.
 */
void Game::resetGame() {
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    if (victoryTexture) {
        SDL_DestroyTexture(victoryTexture);
        victoryTexture = nullptr;
    }

    spawnEnemies();
}

/**
 * @brief Выполняет один кадр игрового цикла.
 * 
 * Отрисовка выполняется в следующем порядке:
 * 1. Очистка экрана тёмно-серым цветом
 * 2. Отрисовка градиентного фона (если он создан)
 * 3. Отрисовка всех врагов (активные отображаются, неактивные - нет)
 * 4. Если активен экран победы, отрисовка полупрозрачного оверлея
 *    и текстуры победы поверх него
 * 5. Показ отрендеренного кадра на экране
 * 
 * @return Всегда возвращает SDL_APP_CONTINUE.
 */
SDL_AppResult Game::SDL_AppIterate()
{
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    if (backgroundTexture) {
        SDL_RenderTexture(renderer, backgroundTexture, NULL, &mainrect);
    }

    for (Enemy* enemy : enemies) {
        enemy->update();
        enemy->draw();
    }

    if (victoryScreen && victoryTexture) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
        SDL_FRect overlayRect = { 0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT };
        SDL_RenderFillRect(renderer, &overlayRect);
        SDL_RenderTexture(renderer, victoryTexture, NULL, &victoryRect);
    }

    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}

/**
 * @brief Освобождает все ресурсы перед выходом из приложения.
 * 
 * Уничтожает окно и рендерер, закрывает шрифт,
 * завершает работу подсистем SDL_ttf и SDL.
 * 
 * @param result Результат работы приложения (не используется напрямую).
 */
void Game::SDL_AppQuit(SDL_AppResult result)
{
    if (window) SDL_DestroyWindow(window);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (font) TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}
