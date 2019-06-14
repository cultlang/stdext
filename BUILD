cc_library(
    name="stdext",
    visibility = ["//visibility:public"],
    hdrs=glob([
        "src/**/*.h*",
    ]),
    srcs=glob([
        "src/**/*.c*"
    ]),
    includes=[
        "src"
    ],
    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
        "@bazel_tools//src/conditions:darwin": ["-std=c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
    deps=[
        "@fmt//:fmt",
        "@catch//:single_include",
    ]
)

cc_test(
    name = "test",
    srcs = glob(["test/**/*.cpp"]),
    deps = [
        ":stdext",
        "@catch//:single_include",
    ],
)