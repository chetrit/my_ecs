/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-alexandre.chetrit
** File description:
** clock
*/

#ifdef SFML_PLUGIN
#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include "SFML/Graphics.hpp"

namespace ecs {
class clock_t {
  public:
    clock_t(int32_t const &interval_) : interval(interval_), _clock(){};
    ~clock_t() = default;

    uint16_t get_nb_frames_to_compute(bool restartClock = true) {
        uint16_t nb_frames = (uint16_t)((get_elapsed_time() + _remaining_time) / interval);
        if (restartClock) {
            _remaining_time = get_elapsed_time() - nb_frames * interval;
            restart_clock();
        }
        return nb_frames;
    }

    int32_t interval;

  private:
    sf::Clock _clock;
    int32_t _remaining_time = 0;

    void restart_clock() { _clock.restart(); };

    int32_t get_elapsed_time() { return _clock.getElapsedTime().asMilliseconds(); };
};
}  // namespace ecs

#endif /* !CLOCK_HPP_ */
#endif
