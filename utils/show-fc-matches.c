#include <stdio.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <fontconfig/fontconfig.h>

void f (char* family)
{
  FcConfig* config = FcInitLoadConfigAndFonts();
  FcObjectSet *os = FcObjectSetBuild (FC_FAMILY, FC_SPACING, FC_STYLE, FC_WEIGHT, FC_WIDTH, FC_SLANT, FC_VARIABLE, FC_FONTFORMAT, NULL);
  FcPattern *pat = FcPatternCreate ();
  FcFontSet *fontset = FcFontList (config, pat, os);
  FcPatternDestroy (pat);
  FcObjectSetDestroy (os);

  int i;
  for (i = 0; i < fontset->nfont; i++)
  {
    char *s;
    FcResult res;
    int spacing;

    res = FcPatternGetString (fontset->fonts[i], FC_FONTFORMAT, 0, (FcChar8 **)(void*)&s);
    if (res != FcResultMatch)
      continue;

    res = FcPatternGetString (fontset->fonts[i], FC_FAMILY, 0, (FcChar8 **)(void*)&s);

    if (strcmp(s, family) == 0) {
      res = FcPatternGetInteger (fontset->fonts[i], FC_SPACING, 0, &spacing);
      printf("Family: %s, spacing: %d\n", family, spacing);
      FcPatternPrint(fontset->fonts[i]);
    }
    res = FcPatternGetInteger (fontset->fonts[i], FC_SPACING, 0, &spacing);
    if (res == FcResultNoMatch)
      spacing = FC_PROPORTIONAL;
  }
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf (stderr, "Usage: %s <font pattern>\n", argv[0]);
    return 1;
  }

  f (argv[1]);
  return 0;
}
