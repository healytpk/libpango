/* Pango
 * pangofc-fontmap.h: Base fontmap type for fontconfig-based backends
 *
 * Copyright (C) 2003 Red Hat Software
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __PANGO_FC_FONT_MAP_PRIVATE_H__
#define __PANGO_FC_FONT_MAP_PRIVATE_H__

#include <pango/pangofc-fontmap.h>
#include <pango/pangofc-decoder.h>
#include <pango/pangofc-font-private.h>
#include <pango/pango-fontmap.h>
#include <pango/pango-fontset.h>

#include <fontconfig/fontconfig.h>

G_BEGIN_DECLS


/**
 * PangoFcFontsetKey:
 *
 * An opaque structure containing all the information needed for
 * loading a fontset with the PangoFc fontmap.
 *
 * Since: 1.24
 **/
typedef struct _PangoFcFontsetKey  PangoFcFontsetKey;

PANGO_AVAILABLE_IN_1_24
PangoLanguage              *pango_fc_fontset_key_get_language      (const PangoFcFontsetKey *key);
PANGO_AVAILABLE_IN_1_24
const PangoFontDescription *pango_fc_fontset_key_get_description   (const PangoFcFontsetKey *key);
PANGO_AVAILABLE_IN_1_24
const PangoMatrix          *pango_fc_fontset_key_get_matrix        (const PangoFcFontsetKey *key);
PANGO_AVAILABLE_IN_1_24
double                      pango_fc_fontset_key_get_absolute_size (const PangoFcFontsetKey *key);
PANGO_AVAILABLE_IN_1_24
double                      pango_fc_fontset_key_get_resolution    (const PangoFcFontsetKey *key);
PANGO_AVAILABLE_IN_1_24
gpointer                    pango_fc_fontset_key_get_context_key   (const PangoFcFontsetKey *key);

/**
 * PangoFcFontKey:
 *
 * An opaque structure containing all the information needed for
 * loading a font with the PangoFc fontmap.
 *
 * Since: 1.24
 **/
typedef struct _PangoFcFontKey     PangoFcFontKey;

PANGO_AVAILABLE_IN_1_24
const FcPattern   *pango_fc_font_key_get_pattern     (const PangoFcFontKey *key);
PANGO_AVAILABLE_IN_1_24
const PangoMatrix *pango_fc_font_key_get_matrix      (const PangoFcFontKey *key);
PANGO_AVAILABLE_IN_1_24
gpointer           pango_fc_font_key_get_context_key (const PangoFcFontKey *key);
PANGO_AVAILABLE_IN_1_40
const char        *pango_fc_font_key_get_variations  (const PangoFcFontKey *key);


#define PANGO_FC_FONT_MAP_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), PANGO_TYPE_FC_FONT_MAP, PangoFcFontMapClass))
#define PANGO_IS_FC_FONT_MAP_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), PANGO_TYPE_FC_FONT_MAP))
#define PANGO_FC_FONT_MAP_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), PANGO_TYPE_FC_FONT_MAP, PangoFcFontMapClass))

/**
 * PangoFcFontMap:
 *
 * `PangoFcFontMap` is a base class for font map implementations
 * using the Fontconfig and FreeType libraries. To create a new
 * backend using Fontconfig and FreeType, you derive from this class
 * and implement a new_font() virtual function that creates an
 * instance deriving from `PangoFcFont`.
 **/
struct _PangoFcFontMap
{
  PangoFontMap parent_instance;

  PangoFcFontMapPrivate *priv;

  /* Function to call on prepared patterns to do final
   * config tweaking.
   */
  PangoFcSubstituteFunc substitute_func;
  gpointer substitute_data;
  GDestroyNotify substitute_destroy;
};

/**
 * PangoFcFontMapClass:
 * @default_substitute: (nullable): Substitutes in default
 *  values for unspecified fields in a #FcPattern. This will
 *  be called prior to creating a font for the pattern.
 *  Implementations must call substitute_func if it is
 *  defined. May be  %NULL. Deprecated in favor of
 *  @font_key_substitute().
 * @new_font: Creates a new `PangoFcFont` for the specified
 *  pattern of the appropriate type for this font map. The
 *  @pattern argument must be passed to the "pattern" property
 *  of `PangoFcFont` when you call g_object_new(). Deprecated
 *  in favor of @create_font().
 * @get_resolution: Gets the resolution (the scale factor
 *  between logical and absolute font sizes) that the backend
 *  will use for a particular fontmap and context. @context
 *  may be null.
 * @context_key_get: Gets an opaque key holding backend
 *  specific options for the context that will affect
 *  fonts created by @create_font(). The result must point to
 *  persistant storage owned by the fontmap. This key
 *  is used to index hash tables used to look up fontsets
 *  and fonts.
 * @context_key_copy: Copies a context key. Pango uses this
 *  to make a persistant copy of the value returned from
 *  @context_key_get.
 * @context_key_free: Frees a context key copied with
 *  @context_key_copy.
 * @context_key_hash: Gets a hash value for a context key
 * @context_key_equal: Compares two context keys for equality.
 * @fontset_key_substitute: (nullable): Substitutes in
 *  default values for unspecified fields in a
 *  #FcPattern. This will be called prior to creating a font
 *  for the pattern. Implementations must call substitute_func
 *  if it is defined. May be %NULL.  (Since: 1.24)
 * @create_font: (nullable): Creates a new `PangoFcFont` for
 *  the specified pattern of the appropriate type for this
 *  font map using information from the font key that is
 *  passed in. The @pattern member of @font_key can be
 *  retrieved using pango_fc_font_key_get_pattern() and must
 *  be passed to the "pattern" property of `PangoFcFont` when
 *  you call g_object_new().  If %NULL, new_font() is used.
 *  (Since: 1.24)
 *
 * Class structure for `PangoFcFontMap`.
 **/
struct _PangoFcFontMapClass
{
  /*< private >*/
  PangoFontMapClass parent_class;

  /*< public >*/
  /* Deprecated in favor of fontset_key_substitute */
  void         (*default_substitute) (PangoFcFontMap   *fontmap,
				      FcPattern        *pattern);
  /* Deprecated in favor of create_font */
  PangoFcFont  *(*new_font)          (PangoFcFontMap  *fontmap,
				      FcPattern       *pattern);

  double       (*get_resolution)     (PangoFcFontMap             *fcfontmap,
				      PangoContext               *context);

  gconstpointer (*context_key_get)   (PangoFcFontMap             *fcfontmap,
				      PangoContext               *context);
  gpointer     (*context_key_copy)   (PangoFcFontMap             *fcfontmap,
				      gconstpointer               key);
  void         (*context_key_free)   (PangoFcFontMap             *fcfontmap,
				      gpointer                    key);
  guint32      (*context_key_hash)   (PangoFcFontMap             *fcfontmap,
				      gconstpointer               key);
  gboolean     (*context_key_equal)  (PangoFcFontMap             *fcfontmap,
				      gconstpointer               key_a,
				      gconstpointer               key_b);
  void         (*fontset_key_substitute)(PangoFcFontMap             *fontmap,

				      PangoFcFontsetKey          *fontsetkey,
				      FcPattern                  *pattern);
  PangoFcFont  *(*create_font)       (PangoFcFontMap             *fontmap,
				      PangoFcFontKey             *fontkey);
  /*< private >*/

  /* Padding for future expansion */
  void (*_pango_reserved1) (void);
  void (*_pango_reserved2) (void);
  void (*_pango_reserved3) (void);
  void (*_pango_reserved4) (void);
};

PangoFontDescription *font_description_from_pattern (FcPattern *pattern,
                                                     gboolean   include_size,
                                                     gboolean   shallow);

G_END_DECLS

#include <assert.h>      // assert
#include <stdint.h>      // intptr_t
#include <string.h>      // NULL, memset
#include <stdlib.h>      // malloc, realloc, free, atexit
#include <threads.h>     // call_once, mtx_init
#include <stdatomic.h>   // atomic_int

struct _FcPattern {
    int num, size;
    intptr_t elts_offset;
    struct { atomic_int count; } ref;
};

#define POINTERS_PER_ALLOC (64u)
#define BYTES_PER_ALLOC (POINTERS_PER_ALLOC * sizeof(FcPattern*))
static FcPattern **g_array_of_patterns_to_destroy = NULL;
static unsigned g_count_allocs = 0u;
static mtx_t g_mtx_for_pattern_destroyer;
static once_flag g_flag_for_init_pattern_destroyer = ONCE_FLAG_INIT;

static void AtExit_DestroyAllPatterns(void);

static void InitialiseArrayOfPatternsToDestroy(void)
{
    g_array_of_patterns_to_destroy = malloc(BYTES_PER_ALLOC);
    assert( NULL != g_array_of_patterns_to_destroy );
    g_count_allocs = 1u;
    memset(g_array_of_patterns_to_destroy,0,BYTES_PER_ALLOC);
    mtx_init(&g_mtx_for_pattern_destroyer, mtx_plain);
    atexit(AtExit_DestroyAllPatterns);
}

static void AddPatternToDestructiveArray(FcPattern *const p)
{
    call_once(&g_flag_for_init_pattern_destroyer, InitialiseArrayOfPatternsToDestroy);

    mtx_lock(&g_mtx_for_pattern_destroyer);

    if ( NULL != g_array_of_patterns_to_destroy[POINTERS_PER_ALLOC*(g_count_allocs-1u) + (POINTERS_PER_ALLOC-1u)] )
    {
        g_array_of_patterns_to_destroy = realloc( g_array_of_patterns_to_destroy, BYTES_PER_ALLOC * (1u + g_count_allocs) );
        assert( NULL != g_array_of_patterns_to_destroy );
        ++g_count_allocs;
        memset(g_array_of_patterns_to_destroy + POINTERS_PER_ALLOC*(g_count_allocs - 1u), 0, BYTES_PER_ALLOC);
    }

    FcPattern **first_nullptr = g_array_of_patterns_to_destroy + POINTERS_PER_ALLOC*(g_count_allocs - 1u);
    for ( ; NULL != *first_nullptr; ++first_nullptr ) { /* Do Nothing */ }

    *first_nullptr = p;

    mtx_unlock(&g_mtx_for_pattern_destroyer);
}

static void AtExit_DestroyAllPatterns(void)
{
    for ( unsigned i = 0u; i < (POINTERS_PER_ALLOC*g_count_allocs); ++i )
    {
        FcPattern *const p = g_array_of_patterns_to_destroy[i];

        if ( NULL == p ) break;

        if ( p->ref.count <= 0 ) continue;

        int count = p->ref.count;
        while ( count-- ) FcPatternDestroy(p);
    }

    free(g_array_of_patterns_to_destroy);
    mtx_destroy(&g_mtx_for_pattern_destroyer);
}

#endif /* __PANGO_FC_FONT_MAP_PRIVATE_H__ */
