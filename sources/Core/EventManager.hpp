//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_IEVENTMANAGER_HPP
#define MY_RAYTRACER_IEVENTMANAGER_HPP

#include <queue>

namespace RayTracer {
    namespace Core {

        enum class EventType {
            KEY_A_PRESSED,
            KEY_B_PRESSED,
            KEY_C_PRESSED,
            KEY_D_PRESSED,
            KEY_E_PRESSED,
            KEY_F_PRESSED,
            KEY_G_PRESSED,
            KEY_H_PRESSED,
            KEY_I_PRESSED,
            KEY_J_PRESSED,
            KEY_K_PRESSED,
            KEY_L_PRESSED,
            KEY_M_PRESSED,
            KEY_N_PRESSED,
            KEY_O_PRESSED,
            KEY_P_PRESSED,
            KEY_Q_PRESSED,
            KEY_R_PRESSED,
            KEY_S_PRESSED,
            KEY_T_PRESSED,
            KEY_U_PRESSED,
            KEY_V_PRESSED,
            KEY_W_PRESSED,
            KEY_X_PRESSED,
            KEY_Y_PRESSED,
            KEY_Z_PRESSED,
            KEY_0_PRESSED,
            KEY_1_PRESSED,
            KEY_2_PRESSED,
            KEY_3_PRESSED,
            KEY_4_PRESSED,
            KEY_5_PRESSED,
            KEY_6_PRESSED,
            KEY_7_PRESSED,
            KEY_8_PRESSED,
            KEY_9_PRESSED,
            KEY_UP_PRESSED,
            KEY_DOWN_PRESSED,
            KEY_LEFT_PRESSED,
            KEY_RIGHT_PRESSED,
            KEY_SPACE_PRESSED,
            KEY_ENTER_PRESSED,
            KEY_ESCAPE_PRESSED,
            KEY_BACKSPACE_PRESSED,
            KEY_TAB_PRESSED,
            KEY_SHIFT_PRESSED,
            KEY_CTRL_PRESSED,
            KEY_ALT_PRESSED,
            KEY_F1_PRESSED,
            KEY_F2_PRESSED,
            KEY_F3_PRESSED,
            KEY_F4_PRESSED,
            KEY_F5_PRESSED,
            KEY_F6_PRESSED,
            KEY_F7_PRESSED,
            KEY_F8_PRESSED,
            KEY_F9_PRESSED,
            KEY_F10_PRESSED,
            KEY_F11_PRESSED,
            KEY_F12_PRESSED,
            QUIT,
        };

        class EventManager {
            public:
                EventManager() = default;
                ~EventManager() = default;

                void addEvent(EventType &type);
                void addEvent(EventType &&type);
                void removeEvent(EventType &type);
                void removeEvent(EventType &&type);
                void clearEvents();
                bool isEventTriggered(const EventType &type);
                bool isEventTriggered(const EventType &&type);
            private:
                std::vector<EventType> _events;
        };

    } // Raytracer
} // Core

#endif //MY_RAYTRACER_IEVENTMNAGER_HPP
