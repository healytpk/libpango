if fontconfig_dep.found()
  common_cflags  += [ '-ggdb3', '-fsanitize=address,leak,undefined,pointer-compare,pointer-subtract,float-divide-by-zero,float-cast-overflow', '-fsanitize-address-use-after-scope', '-fcf-protection=full', '-fstack-protector-all', '-fstack-clash-protection', '-fvtv-debug', '-fvtv-counts', '-finstrument-functions', '-D_GLIBC_DEBUG', '-D_GLIBC_DEBUG_PEDANTIC', '-D_GLIBCXX_DEBUG', '-D_GLIBCXX_DEBUG_PEDANTIC' ]
  common_ldflags += [ '-ggdb3', '-fsanitize=address,leak,undefined,pointer-compare,pointer-subtract,float-divide-by-zero,float-cast-overflow', '-fsanitize-address-use-after-scope', '-fcf-protection=full', '-fstack-protector-all', '-fstack-clash-protection', '-fvtv-debug', '-fvtv-counts', '-finstrument-functions', '-D_GLIBC_DEBUG', '-D_GLIBC_DEBUG_PEDANTIC', '-D_GLIBCXX_DEBUG', '-D_GLIBCXX_DEBUG_PEDANTIC' ]

  executable('gen-script-for-lang', 'gen-script-for-lang.c',
             dependencies: pango_deps + [ libpango_dep ],
             link_args: common_ldflags,
             c_args: common_cflags + pango_debug_cflags + [ '-DPANGO_DISABLE_DEPRECATED' ],
             include_directories: root_inc,
             install: false)
endif
