#include "HandlerCoins.h"

uint16_t shs::HandleCoins::getSum() const {
 // uint16_t res_sum{}; 
 return 0;
 // for (auto& x : m_coins)
 ///   res_sum += x.value * x.value;
 // return res_sum;
}

uint16_t shs::HandleCoins::getSumCoin(const uint8_t value) const {
  //auto it = m_coins.get(value);
 // if (it == m_coins.end)
    return 0xffff;
 // return it.value * it.counter;
}


uint16_t shs::HandleCoins::getActiveSum() {
  if (m_active_time_point.seconds() > NOTIFICATION_DELAY && m_active_sum) {
    auto value = m_active_sum;

    m_active_sum = 0;
    return value;
  }
  return 0;
}

void shs::HandleCoins::start() {
  m_ir.setup();
  m_ir.update();

  m_ir_empty = analogRead(0);
  m_ir_last = m_ir_empty;
}

void shs::HandleCoins::tick() {
  
  //m_ir.updateFast();
  uint16_t ir_value = analogRead(0);
  m_coin_flag = false;
  //doutln(ir_value);

  if (ir_value > m_ir_last) m_ir_last = ir_value;
  if (!(ir_value - m_ir_empty > 3))
    return;

  if ((abs(ir_value - m_ir_empty) < 2)) {
    m_coin_flag = true;
    doutln("flag!");
    //if (m_register_coin_value) m_coins.attach(std::move(Coin(m_register_coin_value, m_ir_last)));

  //  for (auto& coin : m_coins) {
      // auto delta = abs(m_ir_last - coin.ir_value);
      // if (delta < 30) {
      //   coin.counter++;
       //  m_active_sum += coin.value;

        m_active_time_point.reset();
     // }
    }
  }

