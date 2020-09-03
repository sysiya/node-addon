{
    "targets": [
        {
            "target_name": "addon",  # addon.node
            "sources": ["src/*.cc"],  # entry
            # paths that include header files
            "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")"],
            "cflags_cc": [
                "-std=c++17"  # use c++17 standard
            ],
            "cflags!": ["-fno-exceptions"],  # disable exceptions
            "cflags_cc!": ["-fno-exceptions"],  # disable exceptions
            "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS", "NODE_ADDON_API_DISABLE_DEPRECATED"]
        }
    ]
}
