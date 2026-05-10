#pragma once

namespace fc {

enum class FlightState {
    Idle, // система включается
    Ready, // всё работает, к пуску готово
    Launch, // фаза старта
    Ascent, // набор высоты
    Apogee, // апогей
    Descent, // снижение
    Landed // посадка
};

const char* toString(FlightState state);

} //namespace fc