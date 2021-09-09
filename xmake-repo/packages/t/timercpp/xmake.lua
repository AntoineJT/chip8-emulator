package("timercpp")
    set_kind("library", {headeronly = true})
    set_homepage("https://github.com/99x/timercpp")
    set_description("Javascript like setTimeout and setInterval for c++ developers")
    set_license("MIT")

    -- this header only lib is made using C++14
    set_urls("https://github.com/99x/timercpp.git", "https://github.com/AntoineJT/timercpp-cpp17.git")
    add_versions("15_04_2021", "fbf911046b46f4fa68e3a94d004acb3d9de41f10")
    add_versions("cpp17", "cfb799d59b187bc82c2e3437dd20d40061c8390c")

    on_install(function (package)
        os.cp("timercpp.h", package:installdir("include"))
    end)

    -- TODO Test it
    -- on_test(function (package)
    -- end)
