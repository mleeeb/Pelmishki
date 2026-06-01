/**
 * @file Game.h
 * @brief Главный игровой класс, управляющий окном, рендерингом и основным циклом игры.
 * @author Rmeshki
 */

#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Player.h"

class Player;

/**
 * @brief Главный класс игры.
 * @details Отвечает за инициализацию SDL, создание окна и рендерера,
 *          обработку событий, основной игровой цикл и очистку ресурсов.
 *          Использует Callback-интерфейс SDL3 (SDL_AppInit, SDL_AppEvent и т.д.).
 */
class Game
{
public:
	/**
	 * @brief Конструктор игры.
	 */
	Game();
	
	/**
	 * @brief Деструктор игры. Очищает ресурсы.
	 */
	~Game();

	/**
	 * @brief Инициализирует игру (SDL, окно, рендерер, шрифты, игрока).
	 * @return SDL_APP_CONTINUE при успехе, иначе код ошибки.
	 */
	SDL_AppResult SDL_AppInit();
	
	/**
	 * @brief Обрабатывает входящие события (клавиатура, мышь, закрытие окна).
	 * @param event Указатель на событие SDL.
	 * @return SDL_APP_CONTINUE для продолжения, SDL_APP_SUCCESS для выхода.
	 */
	SDL_AppResult SDL_AppEvent(SDL_Event* event);
	
	/**
	 * @brief Основной игровой цикл. Вызывается каждый кадр.
	 * @details Отрисовывает все объекты, обновляет логику игры.
	 * @return SDL_APP_CONTINUE для продолжения, иначе код остановки.
	 */
	SDL_AppResult SDL_AppIterate();
	
	/**
	 * @brief Завершает работу игры и освобождает ресурсы.
	 * @param result Результат работы приложения (обычно SDL_APP_SUCCESS или ошибка).
	 */
	void SDL_AppQuit(SDL_AppResult result);

	/**
	 * @brief Основной прямоугольник отрисовки (возможно, для фона или UI).
	 */
	SDL_FRect mainrect;

private:
	SDL_Window* window;     ///< Указатель на главное окно игры.
	SDL_Renderer* renderer; ///< Указатель на рендерер для 2D-отрисовки.
	
	TTF_Font* font;         ///< Шрифт для отображения текста (очки, мана и т.д.).

	Player* player;         ///< Указатель на объект игрока.
};
