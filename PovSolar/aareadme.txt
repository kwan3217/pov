 
CASSINI CK files
==============================================================================
 
   This ``aareadme.txt'' file describes contents of the kernels/ck directory
   of the CASSINI SPICE data server. It was last modified on October 17, 2003.
   Contact Chuck Acton (818-354-3869, Chuck.Acton@jpl.nasa.gov), Lee Elson
   (818-354-4223, Lee.Elson@jpl.nasa.gov), or Boris Semenov (818-354-8136,
   Boris.Semenov@jpl.nasa.gov) if you have any questions regarding the data
   files provided in this directory.
 
 
Brief summary
----------------------------------------------------------
 
   This directory contains SPICE C-Kernel (CK) files for the CASSINI
   spacecraft. C-Kernels contain spacecraft attitude quaternions and
   spacecraft angular rates with spacecraft clock time tags. The CK files
   provided on the Cassini DOM and the NAIF server use the IEEE big-endian
   binary standard. Most of the files in this directory have been
   automatically copied from the CASSINI Project Database (DOM.)
 
 
CK File Naming Scheme
----------------------------------------------------------
 
   This section describes the CASSINI CK file naming convention. Components of
   the name in square brackets [] are required. Components in parentheses ()
   are optional.
 
 
CK files produced by the CASSINI AACS beginning Nov 6, 2003 (03309) have the
following form:
 
           [StartDate]_[EndDate][Type][V]_[xxxxxxxx].[Ext]
 
   where:
 
              [StartDate]   File coverage start date (YYDOY);
 
              [EndDate]     File coverage stop date (YYDOY);
 
              [Type]        Type of the data stored in the file: ``r'' =
                            reconstruction, ``p'' = predict;
 
              [V]           File version. The first file generated for a
                            specific time frame is version ``a''. Subsequent
                            files containing revised information for the same
                            time period are given the next higher version
                            letter -- ``b'', ``c'', etc;
 
              [xxxxxxxxx]   Optional freeform text that describes the sequence
                            phase for which the file was created.
 
              [Ext]         Standard SPICE extension for CK files: ``bc'' for
                            IEEE binary CK files, ``xc'' or ``tc'' for
                            transfer format CK files.
 
   For example, the file:
 
           03215_03220pa_port1.bc
 
   is a binary CK containing predicted data and covers a time period in 2003
   from day of the year 215 to 220. It is the first version created for the
   port 1 sequence generation.
 
 
CKs Produced by CASSINI AACS Team prior to Nov 6, 2003 (03309) are named as
follows:
 
           [StartDate]_[EndDate][Type][V].[Ext]
 
   where:
 
              [StartDate]   File coverage start date (YYMMDD);
 
              [EndDate]     File coverage stop date (YYMMDD);
 
              [Type]        Type of the data stored in the file: ``r'' =
                            reconstruction, ``p'' = predict, ``i'' = improved,
                            etc.;
 
              [V]           File version. The first file generated for a
                            specific time frame is version ``a''. Subsequent
                            files containing revised information for the same
                            time period are given the next higher version
                            letter -- ``b'', ``c'', etc.
 
              [Ext]         Standard SPICE extension for CK files: ``bc'' for
                            IEEE binary CK files, ``xc'' or ``tc'' for
                            transfer format CK files.
 
   For example, the file:
 
           971015_971025ra.bc
 
   is a binary CK containing reconstructed data and covers the time period of
   10/15 - 10/25/97. It is the first version created for this time period.
 
 
CK files generated after May 1, 2005.
 
   Reconstruction files will contain documentation in the comment area that
   includes: DOM label, gap summary, and if the file is a replacement file,
   the purpose of the replacement.
 
   Predict files will contain documentation in the comment area that indicates
   the purpose of the file, coverage start date/time and end date/time, file
   creation date, and if the file is a replacement file, the purpose of the
   replacement.
 
   File naming shall follow the convention:
 
           [StartDate]_[EndDate][Type][V][_xxxxxxxx].[Ext]
 
   where:
 
              [StartDate]    File coverage start date (YYDOY);
 
              [EndDate]      File coverage stop date (YYDOY);
 
              [Type]         Type of the data stored in the file: "r'' =
                             reconstruction, "p'' = predict;
 
              [V]            File version. The first file generated for a
                             specific time frame is version "a''. Subsequent
                             files containing revised information for the same
                             time period are given the next higher version
                             letter -- "b'', "c'', etc;
 
              [_xxxxxxxxx]   Optional for reconstructions, required for
                             predicts. For reconstructions this is a freeform
                             text that can be included to provide the user
                             additional clues about the contents.
 
              [Ext]          Standard SPICE extension for CK files: "bc'' for
                             IEEE binary CK files, "xc'' or "tc'' for transfer
                             format CK files.
 
   For predict files the xxxxxxxxx will contain the following:
 
           Waypoint -- Dual sequence SOP Implementation Waypoint
           port1    -- Dual sequence SOP Implementation Port 1
           port2    -- Dual sequence SOP Implementation Port 2
           port3    -- Dual sequence SOP Implementation Port 3
           sopu     -- Single sequence SOP Update Port1 or 2 depending
                       upon the version
           psiv1    -- PSIV1
           psiv2    -- PSIV2
           fsiv     -- FSIV
 
   For example, files for S23/S24 would be named:
 
           06231_06295pa_waypoint.bc  -- S23/S24 SOP Implementation Waypoint
           06231_06295pb_port1.bc     -- S23/S24 SOP Implementation Port 1
           06231_06295pc_port2.bc     -- S23/S24 SOP Implementation Port 2
           06231_06295pd_port3.bc     -- S23/S24 SOP Implementation Port 3
           06231_06269pa_sopu.bc      -- S23 SOP Update Port1
           06231_06269pb_sopu.bc      -- S23 SOP Update Port2
           06231_06269pc_psiv1.bc     -- S23 PSIV1
           06231_06269pd_psiv2.bc     -- S23 PSIV2
           06231_06269pe_fsiv.bc      -- S23 FSIV
 
   As another example, the file:
 
   03215_03220ra.bc
 
   is a binary CKernel containing reconstructed data that covers a time period
   in 2003 from day of the year 215 to 220. It is the first version of the
   file containing reconstruction and covering that time period.
 
   Reconstruction files will not have overlapping time
   intervals.Reconstruction files will be accompanied by summary and plot data
   that describes differences between the predicted and reconstructed data
   which can be posted on the web for user access.
 
 
Other CKs
 
   The CKs that don't follows the naming schemes described in the previous
   section are special products created by AACS Team or NAIF. The naming
   scheme for these special files is TBD.
 
 
Supplementary/Meta Information Files
----------------------------------------------------------
 
   The only kind of supplementary/meta information files provided with the CK
   files are detached label files.
 
 
Label Files
 
   Detached label files have the same names as the corresponding CK files with
   the additional extension ".lbl" appended at the end.
 
   The labels file do NOT have any specific structure and they contain rather
   ``raw'' information combined from the following sources: file SFDU label
   (if such was present) and contents of the comment area. Most of these
   labels are created automatically "on the fly" and are planned to be
   re-processed before final data archiving with the PDS.
 
