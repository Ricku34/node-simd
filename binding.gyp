{
  "targets": [
    {
      "target_name": "simd",
      "sources": [
      	"src/module.cc",
      	"src/f32x4.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
