package("timercpp")
    set_kind("library", {headeronly = true})
    set_homepage("https://github.com/99x/timercpp")
    set_description("Javascript like setTimeout and setInterval for c++ developers")
    set_license("MIT")

    set_urls("https://github.com/99x/timercpp.git")
    add_versions("15_04_2021", "fbf911046b46f4fa68e3a94d004acb3d9de41f10")

    -- this header only lib is made using C++14
    add_patches("15_04_2021", path.join(os.scriptdir(), "patches", "15_04_2021", "cpp17.patch"), "0a0dab5abc31c6e3000ea4523ee5d377c4641a9c1d3b9201f4005254ec1b9d3d")

    on_install(function (package)
        os.cp("timercpp.h", package:installdir("include"))
    end)

    -- TODO Test it
    -- on_test(function (package)
    -- end)
