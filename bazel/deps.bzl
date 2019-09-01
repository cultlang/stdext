load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def stdext_deps():
    if "catch" not in native.existing_rules():
        http_archive(
            name = "catch",
            url = "https://github.com/cgrinker/Catch2/archive/5e6488fd9949cb41d717a72c8c4603b7e37d68cd.zip",
            sha256 = "91e3e0610572adefa301a6e55ac48ab0a3c8ff61787ce6930e346ff36e86905c",
            strip_prefix = "Catch2-5e6488fd9949cb41d717a72c8c4603b7e37d68cd",
        )

    if "fmt" not in native.existing_rules():
        http_archive(
            name = "fmt",
            urls = ["https://github.com/cgrinker/fmt/archive/f16f77297e6bb4df38d4c858edb3295f55716cb4.zip"],
            strip_prefix = "fmt-f16f77297e6bb4df38d4c858edb3295f55716cb4",
            sha256 = "edcacda20bf46be208fbc49cedee2a8a321005dd833752ccc6aa7a1a9d75dc23",
        )