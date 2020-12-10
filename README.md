# Introduction

Different scientific tools use different [file formats to store tractography streamlines](https://www.nitrc.org/plugins/mwiki/index.php/surfice:MainPage#Supported_Formats) such as Camino [BFloat](http://camino.cs.ucl.ac.uk/index.php?n=Main.Fileformats), DTI Studio [DAT](https://www.mristudio.org/wiki/faq#head-3015271ef8a43c43bd5f42e957a8591a3657e60a), DTI-query/CINCH [PDB](http://graphics.stanford.edu/projects/dti/software/pdb_format.html), MRtrix [TCK](https://mrtrix.readthedocs.io/en/latest/getting_started/image_data.html), TrackVis [TRK](http://www.trackvis.org/docs/?subsect=fileformat), VTK's [FIB/VTK format](https://github.com/scilus/fibernavigator). Each format has inherent strengths and limitations. A team of scientists [discussed the need for a unified format](https://github.com/nipy/nibabel/issues/942), and created a document describing potential [formats](https://docs.google.com/document/d/1GOOlG42rB7dlJizu2RfaF5XNj_pIaVl_6rtBSUhsgbE/edit#heading=h.c6igqydj1hrf) that address weaknesses of existing formats.

Based on this discussion, Francois Rheault [created a Python implementation](https://github.com/frheault/tractography_file_format) for creating and reading a new format named TRX. This format uses the popular zip format as container to store tractography data. 

This repository explores how C code could be used to create a simple library for working with this format. The foundation is a simple [C wrapper for zip](https://github.com/kuba--/zip). The current implementation uses [Rich Geldreich's elegant miniz](https://github.com/richgel999/miniz) to extract and compress the [deflated](https://en.wikipedia.org/wiki/DEFLATE) data. This single-file compression code simplifies development, though a deployed product could leverage [accelerated deflate libraries](https://github.com/cloudflare/zlib).

**This project is still in development.**

# Examples

* Report the contents of a trx file:
```
gcc  -I../src/miniz.h ../src/zip.c trxtest.c -o tst; ./ts
[0]: header.json
[1]: positions.3.float16
[2]: offsets.uint64
[3]: dps/commit_weights.float32
[4]: dps/commit_colors.3.uint8
...
[26]: dpv/color_z.uint8
ALL TEST SUCCESS!

```

