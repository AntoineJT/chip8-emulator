package("timercpp")
    set_kind("library", {headeronly = true})
    set_homepage("https://github.com/99x/timercpp")
    set_description("Javascript like setTimeout and setInterval for c++ developers")
    set_license("MIT")

    -- this header only lib is made using C++14
    set_urls("https://github.com/99x/timercpp.git")
    add_versions("150421", "fbf911046b46f4fa68e3a94d004acb3d9de41f10")
    -- Remove -fconcepts related warnings
    add_patches("150421", path.join(os.scriptdir(), "patches", "150421", "concept.patch"), "5795c1400335119e237b0b9650580fae89ac188887b9cff513b075f6d99354e7")

    on_install(function (package)
        os.cp("timercpp.h", package:installdir("include"))
    end)

    -- TODO Test it
    -- on_test(function (package)
    -- end)
