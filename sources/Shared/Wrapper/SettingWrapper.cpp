#include "SettingWrapper.hpp"

namespace RayTracer {
    namespace Shared {
        SettingWrapper::SettingWrapper(const libconfig::Setting &setting) : _setting(setting) {}


        const char* RayTracer::Shared::SettingWrapper::getName() const {
            return _setting.getName();
        }

        bool RayTracer::Shared::SettingWrapper::isGroup() const {
            return _setting.isGroup();
        }

        bool RayTracer::Shared::SettingWrapper::isArray() const {
            return _setting.isArray();
        }

        bool RayTracer::Shared::SettingWrapper::isList() const {
            return _setting.isList();
        }

        int RayTracer::Shared::SettingWrapper::getLength() const {
            return _setting.getLength();
        }
        bool RayTracer::Shared::SettingWrapper::exists(const std::string &path) const {
            try {
                return _setting.exists(path);
            } catch (const libconfig::SettingNotFoundException &ex) {
                return false;
            }
        }


        template <typename T>
        T RayTracer::Shared::SettingWrapper::get() const {
            return _setting.operator T();
        }

        template <typename T>
        bool RayTracer::Shared::SettingWrapper::lookupValue(const std::string &path, T &value) const {
            return _setting.lookupValue(path, value);
        }

        const SettingWrapper SettingWrapper::operator[](int index) const {
            return SettingWrapper(_setting[index]);
        }
        const SettingWrapper SettingWrapper::operator[](const std::string &key) const {
            return SettingWrapper(_setting[key]);
        }

        std::string SettingWrapper::getValueAsString() const {
            return std::string(_setting.operator const char *());
        }

    } // RayTracer
} // Core
