# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

COPTS = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++latest"],
        "//conditions:default": ["-std=c++2b"],
    })


cc_library(
    name = "headers",
    visibility = ["//visibility:public"],
    
    includes=[
        "src",
    ],
    hdrs = glob([
        "src/**/*.h*",
    ]),
    copts = COPTS,
)

cc_library(
    name = "code",
    visibility = ["//visibility:public"],

    srcs = glob([
        "src/**/*.c*"
    ]),
    deps = [
        ":headers",
    ],
    copts = COPTS,
)

cc_test(
    name = "test",
    srcs = glob(["test/**/*.cpp"]),
    deps = [
        ":code",
        "@catch//:single_include",
    ],
    copts = COPTS,
)