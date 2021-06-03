# stage_m1
Code pour le stage à l'ICM / ISIR, developpement d'une IHM pour la stimulation cérébrale profonde.

### Liens a ajouter one note:  
https://discourse.slicer.org/t/slicer-4-10-summary-highlights-and-changelog/4610
https://www.techiedelight.com/clone-specific-tag-with-git/#:~:text=git%20clone,-You%20can%20also&text=It%20has%20%E2%80%93branch%20option%2C%20which,.&text=If%20you%20only%20need%20the,branches%20in%20the%20cloned%20repository.


### Errors
Au moment de la generation du cmake :  

CMake Error: AUTOUIC for target RenderWindowUISingleInheritance: Test run of "uic" executable "C:/Qt/5.15.2/msvc2019_64/bin/uic.exe" failed.
C:/Qt/5.15.2/msvc2019_64/bin/uic.exe -h  

Exit code 0xc0000135  

> Apparement dans vtk examples dis aue pbm vient de "This approach also ensures that when CMAKE_AUTOUIC is set to ON and subfolders are used we get a build with no errors." coherent mqis pqs solution!

### A mettre one note:  
View nodes are connected with 3D rendering widgets. PlotView with Plotting widgets. Slices (Red, Green, Yellow) with 2D rendering widgets
