{
  "targets": [
    {
      "target_name": "simd",
      "sources": [ "src/module.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
