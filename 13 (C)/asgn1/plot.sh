#!/bin/bash

make clean && make monte_carlo # Rebuild the monte carlo executable .
./monte_carlo -n 1500 > /tmp/data.dat # Place the data points into a file

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
data="/tmp/data.dat"

#dataset for figure 2 (first plot)
i=0
while read -r line
do
	i=$((i+1))
	if [[ $i -eq 1 ]]
	then 
		continue
	fi
	check=$(echo $line | awk '{print $5}')
	if [[ $check -eq 1 ]] 
	then 
		echo $line | awk '{print $3,$4}' >> $tempBlue
	else [[ $check -eq 0 ]]
		echo $line | awk '{print $3,$4}' >> $tempRed
	fi
done < $data

#gnuplot call
gnuplot <<END
  set terminal pdf
  set output "./monte_carlo.pdf
  set zeroaxis
  f(x) = sqrt(1 - (x ** 2))
  plot [0:1] [0:1] "/tmp/tempBlue.dat" with dots title "", "/tmp/tempRed.dat" with dots title "", f(x) with lines title ""
END

#dataset for figure 3 (second plot)
#first seed
./monte_carlo -n 1000 -r 1 > /tmp/data.dat
i=0
temp=0
tempString=""
while read -r line
do
	i=$((i+1))
	if [[ $i -eq 1 ]]
	then
		continue
	fi
	temp=$(echo $line | awk '{print $2}')
	temp1=$(bc <<< "$temp - 3.1415926")
	temp=$(echo $line | awk '{print $1}')
	tempString="$temp $temp1"
	echo "$tempString" >> "$tempGreen"
done < $data

#second seed
./monte_carlo -n 1000 -r 2 > /tmp/data.dat
i=0
temp=0
tempString=""
while read -r line
do
	i=$((i+1))
	if [[ $i -eq 1 ]]
	then
		continue
	fi
	temp=$(echo $line | awk '{print $2}')
	temp1=$(bc <<< "$temp - 3.1415926")
	temp=$(echo $line | awk '{print $1}')
	tempString="$temp $temp1"
	echo "$tempString" >> "$tempBlue"
done < $data

#third seed
./monte_carlo -n 1000 -r 3 > /tmp/data.dat
i=0
temp=0
tempString=""
while read -r line
do
	i=$((i+1))
	if [[ $i -eq 1 ]]
	then
		continue
	fi
	temp=$(echo $line | awk '{print $2}')
	temp1=$(bc <<< "$temp - 3.1415926")
	temp=$(echo $line | awk '{print $1}')
	tempString="$temp $temp1"
	echo "$tempString" >> "$tempRed"
done < $data


#gnuplot call
gnuplot <<END
  set terminal pdf
  set output "./mc_error.pdf
  set zeroaxis
  plot [0:1000][-1:1] "/tmp/tempGreen.dat" with lines title "", "/tmp/tempBlue.dat" with lines title "", "/tmp/tempRed.dat" with lines title ""
END