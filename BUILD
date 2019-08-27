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
    name = "stdext",
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
        #"@fmt//:fmt",
    ],
)

cc_test(
    name = "test",
    srcs = glob(["test/**/*.cpp"]),
    deps = [
        ":stdext",
        "@catch//:single_include",
    ],
)