#include "Beeper_Display.h"

/// @brief Defined display client - default: U8G2_SSD1306_128X64_NONAME_1_HW_I2C(U8G2_R0, U8X8_PIN_NONE)
U8G2_SSD1306_128X64_NONAME_1_HW_I2C display_oled = U8G2_SSD1306_128X64_NONAME_1_HW_I2C(U8G2_R0, U8X8_PIN_NONE);

/// @brief [INTERNAL] Calculate max. limit for select index
/// @param length Number of items
/// @return Max. limit
uint8_t _display_getSelectLimit(uint8_t *length)
{
    return *length < DISPLAY_MAX_LINES ? *length - 1 : DISPLAY_MAX_LINES - 1;
}

/// @brief [INTERNAL] Calculate max. limit for start index
/// @param length Number of items
/// @return Max. limit
uint8_t _display_getStartLimit(uint8_t *length)
{
    return *length > DISPLAY_MAX_LINES ? *length - DISPLAY_MAX_LINES : 0;
}

/// @brief [INTERNAL] Recalculate indexes fro render for display next item
/// @param menu Menu of items
void _display_next(menu_items_t *menu)
{
    if (menu->select_pos < _display_getSelectLimit(&(menu->length)))
    {
        menu->select_pos++;
        return;
    }

    if (menu->start_pos >= _display_getStartLimit(&(menu->length)))
        return;

    menu->start_pos++;
}

/// @brief [INTERNAL] Recalculate indexes fro render for display previous item
/// @param menu Menu of items
void _display_prev(menu_items_t *menu)
{
    if (menu->select_pos > 0)
    {
        menu->select_pos--;
        return;
    }

    if (menu->start_pos <= 0)
        return;

    menu->start_pos--;
}

/// @brief Display initialize
void display_begin()
{
    display_oled.setBusClock(400000);
    display_oled.begin();
    display_oled.setBitmapMode(1);
}

/// @brief Generate message position center before render
/// @param message Text for render
/// @param onlyHorizontal Only horizontal align, not vertical - 1 (turn on), 0 (turn off); default: 0
/// @param y Y position or y offset - default: 0
void display_center(const char *message, uint8_t onlyHorizontal, int8_t y)
{
    if (!onlyHorizontal)
    {
        display_oled.setFontPosCenter();
        display_oled.drawStr(
            ((display_oled.getDisplayWidth() - display_oled.getUTF8Width(message)) / 2),
            ((display_oled.getDisplayHeight() - 3) / 2) + y,
            message);
        return;
    }

    display_oled.drawStr(
        ((display_oled.getDisplayWidth() - display_oled.getUTF8Width(message)) / 2),
        y,
        message);
    return;
}

/// @brief Render 1 line message in terminal style
/// @param message Text for render
/// @param center Center text - 1 (turn on), 0 (turn off); default: 0
/// @param onlyHorizontal Only horizontal align, not vertical - 1 (turn on), 0 (turn off); default: 0
/// @param delayMS Min. delay to showing text - default: 2000 ms
void display_terminal(const char *message, uint8_t center, uint8_t onlyHorizontal, uint32_t delayMS)
{
    display_oled.setFont(u8g_font_6x10);
    display_oled.setFontPosTop();

    display_oled.firstPage();
    do
    {
        if (center)
        {
            display_center(message, onlyHorizontal);
            continue;
        }

        display_oled.drawStr(
            0, 0,
            message);
    } while (display_oled.nextPage());
    delay(delayMS);
}

/// @brief Render 2 lines messages in terminal style
/// @param message1 1st text for render
/// @param message2 2nd text for render
/// @param center Center text - 1 (turn on), 0 (turn off); default: 0
/// @param onlyHorizontal Only horizontal align, not vertical - 1 (turn on), 0 (turn off); default: 0
/// @param delayMS Min. delay to showing text - default: 2000 ms
void display_terminal2Lines(const char *message1, const char *message2, uint8_t center, uint8_t onlyHorizontal, uint32_t delayMS)
{
    display_oled.setFont(u8g_font_6x10);
    display_oled.setFontPosTop();

    display_oled.firstPage();
    do
    {
        if (center)
        {
            display_center(message1, onlyHorizontal, onlyHorizontal ? 0 : -10);
            display_center(message2, onlyHorizontal, 10);
            continue;
        }

        display_oled.drawStr(
            0, 0,
            message1);
        display_oled.drawStr(
            0, 10,
            message2);
    } while (display_oled.nextPage());
    delay(delayMS);
}

/// @brief Render menu
/// @param menu Menu of items
void display_renderMenu(menu_items_t *menu)
{
    buzzer_stop();

    display_oled.firstPage();
    do
    {
        // first menu item icon
        display_oled.drawXBM(
            DISPLAY_X_POS_ICON,
            DISPLAY_Y_POS_ICON + 1,
            DISPLAY_W_SIZE_ICON,
            DISPLAY_H_SIZE_ICON,
            menu->items[menu->start_pos].icon);

        // second menu item icon
        if (menu->length >= 2)
        {
            display_oled.drawXBM(
                DISPLAY_X_POS_ICON,
                DISPLAY_Y_POS_ICON + DISPLAY_Y_OFFSET,
                DISPLAY_W_SIZE_ICON,
                DISPLAY_H_SIZE_ICON,
                menu->items[menu->start_pos + 1].icon);
        }

        // third menu item icon
        if (menu->length >= 3)
        {
            display_oled.drawXBM(
                DISPLAY_X_POS_ICON,
                DISPLAY_Y_POS_ICON + 1 + 2 * DISPLAY_Y_OFFSET,
                DISPLAY_W_SIZE_ICON,
                DISPLAY_H_SIZE_ICON,
                menu->items[menu->start_pos + 2].icon);
        }

        display_oled.setFont(DISPLAY_FONT_STYLE);

        display_oled.drawStr(
            DISPLAY_X_POS_FONT,
            DISPLAY_Y_OFFSET_FONT,
            menu->items[menu->start_pos].name);

        if (menu->length >= 2)
        {
            display_oled.drawStr(
                DISPLAY_X_POS_FONT,
                DISPLAY_Y_OFFSET + DISPLAY_Y_OFFSET_FONT,
                menu->items[menu->start_pos + 1].name);
        }

        if (menu->length >= 3)
        {
            display_oled.drawStr(
                DISPLAY_X_POS_FONT,
                2 * DISPLAY_Y_OFFSET + DISPLAY_Y_OFFSET_FONT,
                menu->items[menu->start_pos + 2].name);
        }

        // select rectangle
        display_oled.drawXBM(
            DISPLAY_X_POS_SELECT_RECTANGLE,
            DISPLAY_Y_OFFSET * menu->select_pos,
            DISPLAY_W_SIZE_SELECT_RECTANGLE,
            DISPLAY_H_SIZE_SELECT_RECTANGLE,
            xbm_fn_select_rectangle_bits);

        // scroll points
        display_oled.drawXBM(
            DISPLAY_X_POS_SCROLL_POINTS,
            DISPLAY_Y_POS_SCROLL_POINTS,
            DISPLAY_W_SIZE_SCROLL_POINTS,
            DISPLAY_H_SIZE_SCROLL_POINTS,
            xbm_fn_scroll_points_bits);

        // scroll rectangle
        display_oled.setDrawColor(0);
        display_oled.drawRBox(
            DISPLAY_X_POS_SCROLL_RECTANGLE,
            (DISPLAY_Y_OFFSET_SCROLL_RECTANGLE / (menu->length - 1)) * menu->getSelectedId(),
            DISPLAY_W_SIZE_SCROLL_RECTANGLE,
            DISPLAY_H_SIZE_SCROLL_RECTANGLE,
            DISPLAY_ROUND_SCROLL_RECTANGLE);

        display_oled.setDrawColor(1);
        display_oled.drawRFrame(
            DISPLAY_X_POS_SCROLL_RECTANGLE,
            (DISPLAY_Y_OFFSET_SCROLL_RECTANGLE / (menu->length - 1)) * menu->getSelectedId(),
            DISPLAY_W_SIZE_SCROLL_RECTANGLE,
            DISPLAY_H_SIZE_SCROLL_RECTANGLE,
            DISPLAY_ROUND_SCROLL_RECTANGLE);

    } while (display_oled.nextPage());
    enc_start();
    delay(100);
    btn_start();
}

/// @brief Scroll menu and re-render
/// @param menu Menu of items
/// @param decending Scrolling descending - 1 (descending), 0 (ascending)
void display_scroll(menu_items_t *menu, uint8_t decending)
{
    if (decending)
        _display_next(menu);
    else
        _display_prev(menu);
    display_renderMenu(menu);
}

/// @brief Clear display
void display_off()
{
    display_oled.clearDisplay();
}

//* -------------------------------
//* END