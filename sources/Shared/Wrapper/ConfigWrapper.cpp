//
// Created by Bartosz on 5/5/23.
//

#include "ConfigWrapper.hpp"

namespace RayTracer {
    namespace Shared {
        ConfigWrapper::ConfigWrapper() {}

        bool ConfigWrapper::readFile(const std::string &filename) {
            try {
                cfg.readFile(filename.c_str());
                return true;
            } catch(const libconfig::FileIOException &fioex) {
                return false;
            } catch(const libconfig::ParseException &pex) {
                return false;
            }
        }

        bool ConfigWrapper::writeToFile(const std::string &filename) {
            try {
                cfg.writeFile(filename.c_str());
                return true;
            } catch(const libconfig::FileIOException &fioex) {
                return false;
            }
        }

        SettingWrapper ConfigWrapper::getRoot() const {
            const libconfig::Setting &root = cfg.getRoot();
            return SettingWrapper(root);
        }

        template <typename T>
        bool ConfigWrapper::lookup(const std::string &path, T &value) {
            try {
                value = cfg.lookup(path);
                return true;
            } catch(const libconfig::SettingNotFoundException &nfex) {
                return false;
            }
        }
    } // RayTracer
} // Core