/* Pango
 *
 * Copyright (C) 2000 Red Hat Software
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

#pragma once

#include <pango/pango-font-face.h>

G_BEGIN_DECLS

struct _PangoFontFace
{
  GObject parent_instance;
};

typedef struct _PangoFontFaceClass PangoFontFaceClass;

struct _PangoFontFaceClass
{
  GObjectClass parent_class;

  /*< public >*/

  const char           * (*get_face_name)  (PangoFontFace *face);
  PangoFontDescription * (*describe)       (PangoFontFace *face);
  void                   (*list_sizes)     (PangoFontFace  *face,
                                            int           **sizes,
                                            int            *n_sizes);
  gboolean               (*is_synthesized) (PangoFontFace *face);
  PangoFontFamily *      (*get_family)     (PangoFontFace *face);

  /*< private >*/

  /* Padding for future expansion */
  void (*_pango_reserved3) (void);
  void (*_pango_reserved4) (void);
};

#define PANGO_FONT_FACE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), PANGO_TYPE_FONT_FACE, PangoFontFaceClass))
#define PANGO_IS_FONT_FACE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), PANGO_TYPE_FONT_FACE))
#define PANGO_FONT_FACE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), PANGO_TYPE_FONT_FACE, PangoFontFaceClass))

G_END_DECLS