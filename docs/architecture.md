# Архитектура проекта

## 1. Назначение проекта

Проект представляет собой учебный программный прототип бортового компьютера ракеты, реализованный на языке C++17.

Цель проекта — показать объектно-ориентированную архитектуру системы, которая:
- получает данные от датчиков;
- агрегирует телеметрию;
- определяет фазу полёта;
- ведёт журнал работы;
- может быть в будущем перенесена на embedded-платформу.

Текущая версия проекта ориентирована на запуск на компьютере и использует имитацию датчиков через генератор сценария.

---

## 2. Архитектурная идея

Проект строится по слоистой архитектуре.

Он делится на три основных слоя:

1. **Core** — платформонезависимое ядро логики.
2. **Desktop layer** — текущая реализация для демонстрации и тестов.
3. **Embedded layer** — будущая реализация для реального железа.

Главный принцип архитектуры:

> Логика полёта должна быть отделена от способа получения данных, способа логирования и конкретной аппаратной платформы.

Именно поэтому ядро должно зависеть не от конкретных реализаций, а от интерфейсов.

---

## 3. Слои архитектуры

### 3.1. Core layer

Core layer содержит основную бизнес-логику проекта.

Этот слой должен работать одинаково:
- на обычном ПК;
- в тестах;
- в будущей embedded-версии.

В `core` входят:
- структуры данных;
- интерфейсы модулей;
- автомат состояний полёта;
- агрегатор телеметрии;
- главный координирующий класс `FlightComputer`.

Core **не должен зависеть** от:
- консольного ввода/вывода;
- чтения файлов сценария;
- конкретных библиотек для SPI/I2C/UART;
- драйверов конкретных датчиков;
- desktop- или embedded-специфичного кода.

### 3.2. Desktop layer

Desktop layer нужен для текущей учебной версии проекта.

Он обеспечивает:
- генерацию тестовых данных;
- mock-реализации датчиков;
- логирование в обычный файл;
- пошаговое время через простой счётчик;
- запуск демонстрационного приложения.

Этот слой позволяет разрабатывать и отлаживать проект без реального железа.

### 3.3. Embedded layer

Embedded layer в текущей версии может отсутствовать или быть представлен только заготовками.

В будущем в этот слой должны войти:
- реальные драйверы датчиков;
- логирование на SD-карту, flash или UART;
- источник времени от аппаратного таймера;
- инициализация платы;
- взаимодействие с периферией микроконтроллера.

---

## 4. Основные архитектурные принципы

### 4.1. Разделение ответственности

Каждый класс должен решать одну главную задачу.

Примеры:
- датчик отвечает только за получение измерения;
- логгер отвечает только за сохранение информации;
- автомат состояний отвечает только за определение фазы полёта;
- `FlightComputer` координирует работу остальных компонентов.

### 4.2. Инверсия зависимостей

Ядро проекта должно работать через абстракции:
- `Sensor`
- `Logger`
- `Clock`

Это позволяет:
- заменить mock-датчики на реальные;
- заменить файловый логгер на логгер для SD-карты;
- заменить пошаговые часы на аппаратный таймер.

### 4.3. Подготовка к переносу на embedded

Проект должен проектироваться как переносимое ядро с временной desktop-обвязкой.

Это означает, что:
- основная логика не должна использовать desktop-зависимые конструкции;
- интерфейсы должны быть стабильными;
- доступ к железу должен быть вынесен за пределы `core`.

### 4.4. Простота и предсказуемость

Код должен быть простым, читаемым и пригодным для расширения.

Для этого рекомендуется:
- избегать сложных иерархий наследования;
- избегать скрытых зависимостей;
- минимизировать побочные эффекты;
- делать небольшие методы;
- явно описывать состояния и переходы.

---

## 5. Структура каталогов

Предлагаемая структура проекта:

```text
rocket_flight_computer/
├── CMakeLists.txt
├── README.md
├── docs/
│   └── architecture.md
│
├── src/
│   ├── core/
│   │   ├── data/
│   │   ├── interfaces/
│   │   ├── flight/
│   │   ├── services/
│   │   └── utils/
│   │
│   ├── desktop/
│   │   ├── simulation/
│   │   ├── sensors/
│   │   ├── logging/
│   │   ├── time/
│   │   └── app/
│   │
│   └── embedded/
│       ├── sensors/
│       ├── logging/
│       ├── time/
│       ├── board/
│       └── app/
│
└── tests/
    ├── core/
    └── desktop/
```

Файлы `.hpp` и `.cpp` располагаются рядом внутри тематических модулей.

Такое решение удобно, потому что:
- интерфейс и реализация находятся рядом;
- проще ориентироваться в коде;
- модуль становится самостоятельной единицей;
- структура лучше масштабируется.

---

## 6. Главная диаграмма архитектуры

```text
┌─────────────────────────────────────────────────────────────────────┐
│                         USER / DEMO / TEST                          │
│                (запуск программы, сценарий, просмотр логов)         │
└─────────────────────────────────────────────────────────────────────┘
                                │
                                ▼
┌─────────────────────────────────────────────────────────────────────┐
│                           APPLICATION LAYER                         │
│                                                                     │
│  DesktopApp / main.cpp                                              │
│  - создаёт объекты                                                  │
│  - связывает зависимости                                            │
│  - запускает главный цикл                                           │
└─────────────────────────────────────────────────────────────────────┘
                                │
                                ▼
┌─────────────────────────────────────────────────────────────────────┐
│                              CORE LAYER                             │
│                                                                     │
│  FlightComputer                                                     │
│  - координирует работу системы                                      │
│  - опрашивает датчики                                               │
│  - агрегирует данные                                                │
│  - передаёт данные в логгер                                         │
│  - обновляет состояние полёта                                       │
└─────────────────────────────────────────────────────────────────────┘
        │                         │                         │
        │                         │                         │
        ▼                         ▼                         ▼
┌──────────────────┐   ┌──────────────────────┐   ┌───────────────────┐
│ Sensor Subsystem │   │ State Subsystem      │   │ Logging Subsystem │
│                  │   │                      │   │                   │
│ Sensor           │   │ FlightStateMachine   │   │ Logger            │
│ Mock/RealSensors │   │ FlightState          │   │ File/Sd/UartLogger│
└──────────────────┘   └──────────────────────┘   └───────────────────┘
        │                         ▲                         ▲
        │                         │                         │
        ▼                         │                         │
┌─────────────────────────────────────────────────────────────────────┐
│                         DATA / SERVICE LAYER                        │
│                                                                     │
│  SensorData                                                         │
│  TelemetryFrame                                                     │
│  DataAggregator                                                     │
└─────────────────────────────────────────────────────────────────────┘
        ▲
        │
        │
┌─────────────────────────────────────────────────────────────────────┐
│                       PLATFORM-SPECIFIC LAYER                       │
│                                                                     │
│  DESKTOP VERSION                                                    │
│  - ScenarioGenerator                                                │
│  - MockIMUSensor                                                    │
│  - MockBarometerSensor                                              │
│  - MockTemperatureSensor                                            │
│  - MockBatterySensor                                                │
│  - FileLogger                                                       │
│  - StepClock                                                        │
│                                                                     │
│  EMBEDDED VERSION (future)                                          │
│  - RealIMUSensor                                                    │
│  - RealBarometerSensor                                              │
│  - RealTemperatureSensor                                            │
│  - RealBatterySensor                                                │
│  - SdLogger / UartLogger                                            │
│  - HardwareClock                                                    │
│  - BoardInit / SPI / I2C / UART                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 7. Основные классы и структуры

Ниже приведены ключевые классы, их роли и минимальные варианты интерфейсов, с которых можно начинать написание кода.

### 7.1. `SensorKind` и `SensorData`

`SensorData` — это контейнер для результата одного чтения одного датчика.

```cpp
#include <cstdint>

enum class SensorKind {
    IMU,
    Barometer,
    Temperature,
    Battery
};

struct SensorData {
    SensorKind kind;
    std::uint64_t timestampMs;
    double value1;
    double value2;
    double value3;
    bool valid;
};
```

Смысл полей:
- `kind` — какой датчик дал измерение;
- `timestampMs` — время измерения;
- `value1`, `value2`, `value3` — данные датчика;
- `valid` — корректно ли измерение.

Для IMU можно использовать три значения, для батареи — только `value1`.

---

### 7.2. `TelemetryFrame`

`TelemetryFrame` — это не одно измерение, а собранный снимок текущего состояния системы.

```cpp
#include <cstdint>

struct TelemetryFrame {
    std::uint64_t timestampMs;
    double altitude;
    double accelerationZ;
    double temperature;
    double batteryVoltage;

    bool altitudeValid;
    bool imuValid;
    bool temperatureValid;
    bool batteryValid;
};
```

Именно `TelemetryFrame` удобно передавать:
- в автомат состояний;
- в логгер;
- в будущую телеметрию.

---

### 7.3. `Sensor`

`Sensor` — абстрактный интерфейс датчика.

```cpp
class Sensor {
public:
    virtual ~Sensor() = default;
    virtual bool init() = 0;
    virtual SensorData read(std::uint64_t timestampMs) = 0;
    virtual std::string name() const = 0;
};
```

Задача интерфейса — дать `FlightComputer` возможность одинаково работать с любыми датчиками.

Потом можно сделать:
- `MockIMUSensor`
- `MockBarometerSensor`
- `MockTemperatureSensor`
- `MockBatterySensor`
- `RealIMUSensor`
- `RealBarometerSensor`

---

### 7.4. `Logger`

`Logger` — интерфейс логгера.

```cpp
class Logger {
public:
    virtual ~Logger() = default;
    virtual bool open(const std::string& path) = 0;
    virtual void logFrame(const TelemetryFrame& frame) = 0;
    virtual void logMessage(const std::string& msg) = 0;
    virtual void close() = 0;
};
```

Сейчас реализация может быть `FileLogger`, а потом:
- `SdLogger`
- `UartLogger`
- `FlashLogger`

---

### 7.5. `Clock`

`Clock` — интерфейс источника времени.

```cpp
class Clock {
public:
    virtual ~Clock() = default;
    virtual std::uint64_t nowMs() const = 0;
};
```

Сейчас можно сделать `StepClock`, где время просто растёт на фиксированный шаг. Потом его можно заменить на `HardwareClock` с таймером микроконтроллера.

---

### 7.6. `ScenarioFrame` и `ScenarioGenerator`

Начинать реализацию лучше именно с генератора сценария. Он заменяет реальное железо и сразу даёт данные для отладки.

```cpp
struct ScenarioFrame {
    double altitude;
    double accelerationZ;
    double temperature;
    double batteryVoltage;
};
```

```cpp
class ScenarioGenerator {
public:
    ScenarioFrame next();
    bool hasNext() const;
    void reset();

private:
    std::uint64_t currentStep_ = 0;
};
```

Идея простая: генератор по шагам выдаёт правдоподобную последовательность:
- стояние на старте;
- резкий рост ускорения;
- набор высоты;
- апогей;
- снижение;
- посадка.

---

### 7.7. `DataAggregator`

`DataAggregator` собирает отдельные `SensorData` в один `TelemetryFrame`.

```cpp
class DataAggregator {
public:
    void add(const SensorData& data);
    TelemetryFrame buildFrame() const;
    void reset();

private:
    TelemetryFrame frame_{};
};
```

Это удобный промежуточный класс между датчиками и автоматом состояний.

---

### 7.8. `FlightStateMachine`

`FlightStateMachine` определяет фазу полёта по собранной телеметрии.

```cpp
enum class FlightState {
    Idle,
    Ready,
    Launch,
    Ascent,
    Apogee,
    Descent,
    Landed
};
```

```cpp
class FlightStateMachine {
public:
    FlightState update(const TelemetryFrame& frame);
    FlightState state() const;
    void reset();

private:
    FlightState currentState_ = FlightState::Idle;
    double previousAltitude_ = 0.0;
    bool hasPreviousAltitude_ = false;
};
```

Типичные правила переходов:
- старт — большое ускорение;
- подъём — высота растёт;
- апогей — высота перестала расти;
- снижение — высота падает;
- посадка — высота близка к нулю.

---

### 7.9. `FlightComputer`

`FlightComputer` — центральный координирующий класс.

```cpp
class FlightComputer {
public:
    bool init();
    void step();
    void run(std::size_t stepCount);
    void addSensor(Sensor* sensor);

private:
    std::vector<Sensor*> sensors_;
    Logger& logger_;
    Clock& clock_;
    DataAggregator aggregator_;
    FlightStateMachine stateMachine_;
};
```

Он:
- опрашивает датчики;
- собирает `SensorData`;
- передаёт их в `DataAggregator`;
- получает `TelemetryFrame`;
- логирует данные;
- обновляет фазу полёта.

---

### 7.10. `DesktopApp`

`DesktopApp` — оболочка текущей desktop-версии.

```cpp
class DesktopApp {
public:
    bool setup();
    void run();

private:
    ScenarioGenerator scenario_;
    StepClock clock_;
    FileLogger logger_;
    FlightComputer computer_;
};
```

Её задача — создать все объекты и запустить демонстрационную конфигурацию проекта.

---

## 8. UML-логика связей между классами

```text
DesktopApp
 ├── ScenarioGenerator
 ├── StepClock
 ├── FileLogger
 └── FlightComputer

FlightComputer
 ├── Sensor[*]
 ├── Logger
 ├── Clock
 ├── DataAggregator
 └── FlightStateMachine

Sensor <|-- MockIMUSensor
Sensor <|-- MockBarometerSensor
Sensor <|-- MockTemperatureSensor
Sensor <|-- MockBatterySensor

Logger <|-- FileLogger
Clock  <|-- StepClock

MockIMUSensor ---------> ScenarioGenerator
MockBarometerSensor ---> ScenarioGenerator
MockTemperatureSensor -> ScenarioGenerator
MockBatterySensor -----> ScenarioGenerator

Sensor -------------> SensorData
DataAggregator -----> SensorData
DataAggregator -----> TelemetryFrame
FlightStateMachine -> TelemetryFrame
Logger -------------> TelemetryFrame
```

---

## 9. Поток данных в системе

```text
ScenarioGenerator / Real Sensors
            │
            ▼
   MockSensor / RealSensor
            │
            ▼
        SensorData
            │
            ▼
      DataAggregator
            │
            ▼
      TelemetryFrame
        │         │
        │         │
        ▼         ▼
   FlightStateMachine      Logger
        │
        ▼
   New Flight State
        │
        ▼
   FlightComputer decides what to do next
```

---

## 10. С чего начинать писать код

Начинать надо не с `FlightComputer` и не с `main.cpp`, а с контракта данных и интерфейсов.

### Шаг 1. Зафиксировать минимальный набор данных

Сначала создаются:
1. `SensorData.hpp`
2. `TelemetryFrame.hpp`

### Шаг 2. Написать интерфейсы

Потом создаются:
3. `Sensor.hpp`
4. `Logger.hpp`
5. `Clock.hpp`

### Шаг 3. Сделать генератор сценария

Потом:
6. `ScenarioFrame.hpp`
7. `ScenarioGenerator.hpp/.cpp`

### Шаг 4. Сделать mock-датчики

Потом:
8. `MockIMUSensor.hpp/.cpp`
9. `MockBarometerSensor.hpp/.cpp`
10. `MockTemperatureSensor.hpp/.cpp`
11. `MockBatterySensor.hpp/.cpp`

### Шаг 5. Сделать агрегатор данных

Потом:
12. `DataAggregator.hpp/.cpp`

### Шаг 6. Сделать автомат состояний

Потом:
13. `FlightState.hpp`
14. `FlightStateMachine.hpp/.cpp`

### Шаг 7. Сделать логгер и источник времени

Потом:
15. `FileLogger.hpp/.cpp`
16. `StepClock.hpp/.cpp`

### Шаг 8. Сделать главный координирующий класс

Потом:
17. `FlightComputer.hpp/.cpp`

### Шаг 9. Сделать `main.cpp`

И только в самом конце:
18. `main.cpp`

Это позволяет двум участникам команды работать параллельно и не блокировать друг друга.

---

## 11. Распределение работы на двоих

### Участник 1
Отвечает за:
- `SensorData`
- `TelemetryFrame`
- `ScenarioGenerator`
- mock-датчики

### Участник 2
Отвечает за:
- `Logger`
- `Clock`
- `FlightStateMachine`
- `FlightComputer`

### Совместно
Делают:
- `DataAggregator`
- `main.cpp`
- CMake
- интеграцию
- тесты

---

## 12. Почему такая архитектура подходит для будущего переноса на железо

Эта архитектура удобна тем, что:
- логика не зависит от файлов и консоли;
- источники данных заменяемы;
- логгер заменяем;
- источник времени заменяем;
- mock-реализации легко заменить на реальные.

То есть после сдачи проекта можно будет:
- оставить `core` почти без изменений;
- заменить `MockIMUSensor` на `RealIMUSensor`;
- заменить `FileLogger` на `SdLogger`;
- заменить `StepClock` на `HardwareClock`.

В результате учебный проект становится не одноразовой демонстрацией, а основой для будущей embedded-версии бортового компьютера.
