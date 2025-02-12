#pragma once

#include <stdint.h>
#include <algorithm>
#include <array>

#include <Arduino.h>
#include <FileData.h>
#include <LittleFS.h>


#include <shs_ProgramTime.h>
#include <shs_Process.h>


namespace shs
{
    class HandlerCoins;
};

class shs::HandlerCoins : public shs::Process
{
public:
    HandlerCoins()
        : m_coins({ Coin(1, 981), Coin(2, 1019), Coin(5, 1024), Coin(10, 1000) })
        //m_storage(&LittleFS, "/data.dat", 'B', &m_coins, sizeof(Coin) * 4)
    {}

    static constexpr auto NOTIFICATION_DELAY = 60; // in seconds

    void registerCoin(const uint8_t value) { m_register_coin_value = value; }

    void waiteCoin() { do { tick(); yield(); } while (!m_coin_flag); }
    uint16_t getLastRAW() const { return m_ir_last; }

    [[nodiscard]] uint16_t getSum() const;
    [[nodiscard]] uint16_t getSumCoin(const uint8_t value) const;

    [[nodiscard]] uint16_t getActiveSum() { return m_active_sum; }
    [[nodiscard]] uint16_t takeActiveSum();
    [[nodiscard]] uint32_t getActiveTime() { return m_active_time_point.seconds(); }

    void reset() { for (auto i = 0; i < m_coins.size(); i++) m_coins[i].counter = 0; } // m_storage.write(); }

    void start() override;
    void tick() override;
    void stop() override {}


private:
    struct Coin
    {
        Coin(const uint16_t set_value, const uint16_t set_ir_value = 0, const uint16_t set_counter = 0)
            : value(set_value), counter(set_counter), ir_value(set_ir_value)
        {}

        uint16_t value{};
        uint16_t ir_value{};
        uint16_t counter{};
    };

    struct CoinCompare { bool operator()(const Coin& lhs, const Coin& rhs) const { return lhs.value < rhs.value; } };

    std::array<Coin, 4> m_coins;

    //FileData m_storage;

    shs::ProgramTime m_active_time_point;
    uint16_t m_active_sum{};
    uint8_t m_register_coin_value{};
    bool m_coin_flag{};
    bool m_flag{};

    uint16_t m_ir_empty{};
    uint16_t m_ir_last{};
};
