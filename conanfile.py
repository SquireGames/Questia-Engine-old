from conans import ConanFile, CMake, tools


class QengConan(ConanFile):
    name = "QENG"
    version = "0.0.1"
    folder = "Questia-Engine"
    license = "GPL-3.0"
    url = "https://github.com/SquireGames/Questia-Engine"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    # default_options = "shared=False"
    default_options = "gtest:shared=True", "shared=True"
    generators = "cmake"
    requires = "gtest/1.8.0@bincrafters/stable"

    def source(self):
        self.run("git clone https://github.com/SquireGames/Questia-Engine.git")
        self.run("cd Questia-Engine")  # TODO && git checkout ~")

    def build(self):
        shared = {"BUILD_SHARED_LIBS": self.options.shared}
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src=self.folder)
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        # self.cpp_info.libs = ["hello"]
        pass
              
    def imports(self):
        self.copy("*.dll", "bin", "bin")
        self.copy("*.dylib", "lib", "lib")
