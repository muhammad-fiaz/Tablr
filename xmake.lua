set_project("tablr")
set_version("0.0.0")
set_languages("c11", "cxx17")
set_warnings("all")

add_rules("mode.debug", "mode.release")

if is_mode("release") then
    set_optimize("fastest")
    set_strip("all")
end

option("cuda")
    set_default(false)
    set_showmenu(true)
    set_description("Enable CUDA support")

target("tablr")
    set_kind("static")
    add_files("src/core/*.c")
    add_files("src/io/*.c")
    add_files("src/ops/*.c")
    add_files("src/device/*.c")
    add_includedirs("include", {public = true})
    add_headerfiles("include/(tablr/**.h)")
    
    if has_config("cuda") then
        add_defines("TABLR_CUDA_ENABLED")
        add_cugencodes("native")
        add_files("src/device/*.cu")
    end

target("tests")
    set_kind("binary")
    add_deps("tablr")
    add_files("tests/*.c")
    add_includedirs("include")

target("example_basic")
    set_kind("binary")
    add_deps("tablr")
    add_files("examples/basic_usage.c")
    add_includedirs("include")

target("example_filtering")
    set_kind("binary")
    add_deps("tablr")
    add_files("examples/example_filtering.c")
    add_includedirs("include")

target("example_sorting")
    set_kind("binary")
    add_deps("tablr")
    add_files("examples/example_sorting.c")
    add_includedirs("include")

target("example_device")
    set_kind("binary")
    add_deps("tablr")
    add_files("examples/example_device.c")
    add_includedirs("include")

target("example_aggregation")
    set_kind("binary")
    add_deps("tablr")
    add_files("examples/example_aggregation.c")
    add_includedirs("include")

target("example_csv")
    set_kind("binary")
    add_deps("tablr")
    add_files("examples/example_csv.c")
    add_includedirs("include")
