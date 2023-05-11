#pragma once
#include <string>
#include <stdexcept>
#include <libconfig.h++>


namespace RayTracer {
    namespace Shared {
        class SettingWrapper {
        public:

            class NotFoundException : public std::runtime_error {
            public:
                NotFoundException(const std::string &message, const std::string &path)
                        : std::runtime_error(message), _path(path) {}

                const std::string &getPath() const { return _path; }

            private:
                std::string _path;
            };
            SettingWrapper(const libconfig::Setting &setting);

            const char* getName() const;
            bool isGroup() const;
            bool isArray() const;
            bool isList() const;
            int getLength() const;
            bool exists(const std::string &path) const;


            template <typename T>
            T get() const;

            template <typename T>
            bool lookupValue(const std::string &path, T &value) const;
            template <typename T>
            T lookup(const std::string &path) const {
                try {
                    return _setting.lookup(path);
                } catch (const libconfig::SettingNotFoundException &ex) {
                    throw NotFoundException(ex.what(), path);
                }
            }

            const SettingWrapper operator[](int index) const;
            const SettingWrapper operator[](const std::string &name) const;

            std::string getValueAsString() const;

        private:
            const libconfig::Setting &_setting;
        };
    } // namespace Core
} // namespace RayTracer
