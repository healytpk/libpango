examples = []

if pango_cairo_backends.contains('png')
  examples += [
    'cairoshape',
    'cairosimple',
    'cairotwisted',
  ]
endif

examples_deps = [ libpango_dep, libpangocairo_dep, ]

if pango_font_backends.contains('freetype')
  examples_deps += libpangoft2_dep
endif

# somebody will have to fix this
# if host_system == 'windows'
#   # This hasn't been built in years, most likely, but try now
#   examples += [ 'pangowin32tobmp' ]
#   examples_deps += [ libpangowin32_dep ]
# endif

foreach e: examples
  common_cflags  += [ '-ggdb3', '-fsanitize=address,leak,undefined,pointer-compare,pointer-subtract,float-divide-by-zero,float-cast-overflow', '-fsanitize-address-use-after-scope', '-fcf-protection=full', '-fstack-protector-all', '-fstack-clash-protection', '-fvtv-debug', '-fvtv-counts', '-finstrument-functions', '-D_GLIBC_DEBUG', '-D_GLIBC_DEBUG_PEDANTIC', '-D_GLIBCXX_DEBUG', '-D_GLIBCXX_DEBUG_PEDANTIC' ]
  common_ldflags += [ '-ggdb3', '-fsanitize=address,leak,undefined,pointer-compare,pointer-subtract,float-divide-by-zero,float-cast-overflow', '-fsanitize-address-use-after-scope', '-fcf-protection=full', '-fstack-protector-all', '-fstack-clash-protection', '-fvtv-debug', '-fvtv-counts', '-finstrument-functions', '-D_GLIBC_DEBUG', '-D_GLIBC_DEBUG_PEDANTIC', '-D_GLIBCXX_DEBUG', '-D_GLIBCXX_DEBUG_PEDANTIC' ]

  executable(e, '@0@.c'.format(e),
             dependencies: examples_deps + pango_deps,
             link_args: common_ldflags,
             c_args: common_cflags,
             include_directories: root_inc,
             install: false)
endforeach
