set_project("tablr")
set_version("0.0.1")
set_languages("c11", "cxx17")
set_warnings("all")

add_rules("mode.debug", "mode.release")

if is_plat("windows") then
    add_cxflags("/utf-8")
end

if is_mode("release") then
    set_optimize("fastest")
    set_strip("all")
end

option("cuda")
    set_default(false)
    set_showmenu(true)
    set_description("Enable CUDA support")
    add_defines("TABLR_CUDA_ENABLED")
    on_check(function (option)
        if is_plat("windows") then
            option:add("includedirs", "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.8/include")
            option:add("linkdirs", "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.8/lib/x64")
        end
    end)

option("xpu")
    set_default(false)
    set_showmenu(true)
    set_description("Enable Intel XPU support")

option("npu")
    set_default(false)
    set_showmenu(true)
    set_description("Enable NPU support")

option("tpu")
    set_default(false)
    set_showmenu(true)
    set_description("Enable TPU support")

target("tablr")
    set_kind("static")
    add_files("src/core/*.c")
    add_files("src/io/*.c")
    add_files("src/ops/*.c")
    add_files("src/device/*.c")
    add_includedirs("include", {public = true})
    add_headerfiles("include/(tablr/**.h)")
    
    if has_config("cuda") then
        add_options("cuda")
        add_files("src/device/cuda_ops.cu")
        add_links("cudart")
        if is_plat("windows") then
            add_includedirs("C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.8/include")
            add_linkdirs("C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.8/lib/x64")
        end
    end
    
    if has_config("xpu") then
        add_defines("TABLR_XPU_ENABLED")
        set_languages("cxx17")
        add_files("src/device/xpu_ops.cpp")
        add_syslinks("sycl")
    end
    
    if has_config("npu") then
        add_defines("TABLR_NPU_ENABLED")
        add_files("src/device/npu_ops.c")
    end
    
    if has_config("tpu") then
        add_defines("TABLR_TPU_ENABLED")
        add_files("src/device/tpu_ops.c")
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

target("example_device_switching")
    set_kind("binary")
    add_deps("tablr")
    add_files("examples/example_device_switching.c")
    add_includedirs("include")
