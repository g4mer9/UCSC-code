#setup temp variables
touch /tmp/tempRed.dat
echo -n "" > /tmp/tempRed.dat
tempRed="/tmp/tempRed.dat"
touch /tmp/tempBlue.dat
echo -n "" > /tmp/tempBlue.dat
tempBlue="/tmp/tempBlue.dat"
touch /tmp/tempGreen.dat
echo -n "" > /tmp/tempGreen.dat
tempGreen="/tmp/tempGreen.dat"

for (( i=0; i < 1000; i++ )) do ./sorting -bn i -> tempGreen; done

#gnuplot <<END
#  set terminal pdf
#  set output "./moves_over_elements.pdf
#  set zeroaxis
#  plot [10:1000] [10:1000000] "/tmp/tempBlue.dat" with dots title "", "/tmp/tempRed.dat" with dots title "", f(x) with lines title ""
#END
