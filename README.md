# ENL_egn_Sim for Studies of gammas/neutrons produced by electrons on steel [huber@ecnbg.in2p3.fr, huberarnaud@gmail.com]

# INSTRUCTIONS TO USE THE SIMULATION
# - Download the VMWare Geant4.11.0.0 from https://heberge.lp2ib.in2p3.fr/G4VM/index.html
# - Copy all the files from ENL_egn_Simulation folder (https://github.com/ahuber33/ENL_egn_Simulation)
# - Create a build folder in the ENL_egn_Simulation folder and go inside.
# - Use this command : "cmake -DGeant4_DIR=$G4COMP ../" and compile it with make
# - The executable ENLegnSim will be add to your bin folder
# - If you want to have a visualization, launch this command : "./ENLegnSim [name of ROOT file ]". It will generate 1 particle according to the vis.mac with QT and you will have a ROOT file with the name you gave in response located in the Resultats folder.
# - If you want to have statistics without the visualization, use this command : "./ENLegnSim [name of ROOT file] [number of events generated] [name of macro]". Personnaly, I used the vrml.mac but you can create another one. Just to remember that you need to write the name of your macro when you launch the simulation.
# - An ENLegnSim.cfg file is located in bin directory. All the dimensions necessary are in this file to avoid recompilation when you want to change some parameters. If you add some other dimensions, don't forget to add the variables in Geometry.cc.
# - Based on G4EmStandardPhysics_option3 with additional Photonuclear process pour gammas. All neutron interactions are also taken into account with HP data for neutrons.
# - theRunTree contains all datas about gamma from bremsstrahlung (creation and a the exit of the steel plate), neutrons from (gamma, n) process (creation and a the exit of the steel plate)corresponds to general optical datas from 1 event (number of photons generated, ect). You have also the information about the initial energy of the electron and the energy deposition in to the steel plate.
# - Electron spectrum in input are from the scan08 [VEGA3 Summary Analysis]
# - DO NOT HESITATE TO REPORT BUGS OR ANY IDEAS THAT WILL IMPROVE THE SIMULATION !!!!

# Commit #1 [ENLegnSim.0.0.0]
# - Structure from ENLOpticalSim with a lot of code cleaning (all the optical part).
# - Add of photon nuclear process for gammas (process g,n)
# - Add of NeutronHPphysics
# - Creation of vectors in the ROOT Tree to obtain all datas about gammas and neutrons for each events

#commit #2 [ENLegnSim.0.0.1]
# - Cleaning of vis.mac and vmrl.mac
<<<<<<< HEAD
# - Add a condition for the datas integration -> ROOT files too fat due to IncidentE and deposit if you want information on neutron with stat
=======
# - Add a condition for the datas integration -> ROOT files too fat due to IncidentE and depositi if you want information on neutron with stat
>>>>>>> 674b733f1d724be47e1c0363800f46fc6b385db0
