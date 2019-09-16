cc_library(
    name = "headers",
    visibility = ["//visibility:public"],
    
    deps=[
        "@fmt//:headers",
    ],
    
    includes=[
        "src",
    ],
    hdrs = glob([
        "src/**/*.h*",
    ]),
)

cc_library(
    name = "code",
    visibility = ["//visibility:public"],

    srcs = glob([
        "src/**/*.c*"
    ]),
    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
    deps = [
        ":headers",
    ],
)

cc_test(
    name = "test",
    srcs = glob(["test/**/*.cpp"]),
    deps = [
        ":code",
        "@catch//:single_include",
    ],
    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
)