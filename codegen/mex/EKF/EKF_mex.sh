MATLAB="/usr/local/MATLAB/R2018b"
Arch=glnxa64
ENTRYPOINT=mexFunction
MAPFILE=$ENTRYPOINT'.map'
PREFDIR="/home/danglamtung/.matlab/R2018b"
OPTSFILE_NAME="./setEnv.sh"
. $OPTSFILE_NAME
COMPILER=$CC
. $OPTSFILE_NAME
echo "# Make settings for EKF" > EKF_mex.mki
echo "CC=$CC" >> EKF_mex.mki
echo "CFLAGS=$CFLAGS" >> EKF_mex.mki
echo "CLIBS=$CLIBS" >> EKF_mex.mki
echo "COPTIMFLAGS=$COPTIMFLAGS" >> EKF_mex.mki
echo "CDEBUGFLAGS=$CDEBUGFLAGS" >> EKF_mex.mki
echo "CXX=$CXX" >> EKF_mex.mki
echo "CXXFLAGS=$CXXFLAGS" >> EKF_mex.mki
echo "CXXLIBS=$CXXLIBS" >> EKF_mex.mki
echo "CXXOPTIMFLAGS=$CXXOPTIMFLAGS" >> EKF_mex.mki
echo "CXXDEBUGFLAGS=$CXXDEBUGFLAGS" >> EKF_mex.mki
echo "LDFLAGS=$LDFLAGS" >> EKF_mex.mki
echo "LDOPTIMFLAGS=$LDOPTIMFLAGS" >> EKF_mex.mki
echo "LDDEBUGFLAGS=$LDDEBUGFLAGS" >> EKF_mex.mki
echo "Arch=$Arch" >> EKF_mex.mki
echo "LD=$LD" >> EKF_mex.mki
echo OMPFLAGS= >> EKF_mex.mki
echo OMPLINKFLAGS= >> EKF_mex.mki
echo "EMC_COMPILER=gcc" >> EKF_mex.mki
echo "EMC_CONFIG=optim" >> EKF_mex.mki
"/usr/local/MATLAB/R2018b/bin/glnxa64/gmake" -j 1 -B -f EKF_mex.mk
