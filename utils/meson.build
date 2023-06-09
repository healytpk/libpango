pango_view_sources = [
  'pango-view.c',
  'viewer-main.c',
  'viewer-render.c',
]

pango_view_deps = [
  pango_deps,
  libpango_dep,
]

if build_pangoft2
  pango_view_sources += 'viewer-pangoft2.c'
  pango_view_deps += libpangoft2_dep
endif

if xft_dep.found() and build_pangoft2
  pango_view_sources += [
    'viewer-pangoxft.c',
    'viewer-x.c',
  ]
  pango_view_deps += [ libpangoft2_dep, libpangoxft_dep, ]
endif

if cairo_dep.found()
  pango_view_sources += [
    'viewer-cairo.c',
    'viewer-pangocairo.c',
  ]
  pango_view_deps += libpangocairo_dep
endif

common_cflags  += [ '-ggdb3', '-fsanitize=address,leak,undefined,pointer-compare,pointer-subtract,float-divide-by-zero,float-cast-overflow', '-fsanitize-address-use-after-scope', '-fcf-protection=full', '-fstack-protector-all', '-fstack-clash-protection', '-fvtv-debug', '-fvtv-counts', '-finstrument-functions', '-D_GLIBC_DEBUG', '-D_GLIBC_DEBUG_PEDANTIC', '-D_GLIBCXX_DEBUG', '-D_GLIBCXX_DEBUG_PEDANTIC' ]
common_ldflags += [ '-ggdb3', '-fsanitize=address,leak,undefined,pointer-compare,pointer-subtract,float-divide-by-zero,float-cast-overflow', '-fsanitize-address-use-after-scope', '-fcf-protection=full', '-fstack-protector-all', '-fstack-clash-protection', '-fvtv-debug', '-fvtv-counts', '-finstrument-functions', '-D_GLIBC_DEBUG', '-D_GLIBC_DEBUG_PEDANTIC', '-D_GLIBCXX_DEBUG', '-D_GLIBCXX_DEBUG_PEDANTIC' ]

pango_view = executable('pango-view', pango_view_sources,
                        dependencies: pango_view_deps,
                        include_directories: [ root_inc ],
                        install: true,
                        link_args: common_ldflags,
                        c_args: common_cflags + pango_debug_cflags + [
                          '-DPACKAGE_NAME="@0@"'.format(meson.project_name()),
                          '-DPACKAGE_VERSION="@0@"'.format(meson.project_version()),
                        ])

help2man = find_program('help2man', required: false)
# help2man has to run pango-view to generate the man page, which it can't do if
# we're cross building. We also can't tell help2man what exe wrapper to use.
if help2man.found() and not meson.is_cross_build()
  help2man_opts = [
    '--no-info',
    '--section=1',
    '--help-option=--help-all',
    '--name="Pango text viewer"',
  ]

  custom_target('pango-view.1',
                output: 'pango-view.1',
                command: [
                  help2man, help2man_opts, '--output=@OUTPUT@', pango_view
                ],
                install: true,
                install_dir: join_paths(pango_datadir, 'man/man1'))
endif

if cairo_dep.found()
  pango_list_sources = [
    'pango-list.c',
  ]

  pango_list_deps = [
    pango_deps,
    libpango_dep,
    libpangocairo_dep
  ]

  pango_list = executable('pango-list', pango_list_sources,
                          dependencies: pango_list_deps,
                          include_directories: [ root_inc ],
                          install: true,
                          link_args: common_ldflags,
                          c_args: common_cflags + pango_debug_cflags + [
                           '-DPACKAGE_NAME="@0@"'.format(meson.project_name()),
                           '-DPACKAGE_VERSION="@0@"'.format(meson.project_version()),
                          ])

  pango_segmentation_sources = [
    'pango-segmentation.c',
  ]

  pango_segmentation_deps = [
    pango_deps,
    libpango_dep,
    libpangocairo_dep
  ]

  pango_segmentation = executable('pango-segmentation',
                                  pango_segmentation_sources,
                                  dependencies: pango_segmentation_deps,
                                  include_directories: [ root_inc ],
                                  install: true,
                                  link_args: common_ldflags,
                                  c_args: common_cflags + pango_debug_cflags + [
                                   '-DPACKAGE_NAME="@0@"'.format(meson.project_name()),
                                   '-DPACKAGE_VERSION="@0@"'.format(meson.project_version()),
                                  ])

endif
