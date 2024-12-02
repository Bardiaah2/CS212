#!/bin/bash
gcc -o proj2D proj2D.c -lm
if [ $? -ne 0 ] ; then
   echo "Cannot compile your program"
   echo "Failed"
   exit 1
fi

vals="2071.573632,x,-270.900085;-561189 2236.577152,-,-623.146857;2859 -3633.358177,x,170.062505;-617897 532.411313,x,-2726.849471;-1451805 -881.712246,x,3244.099198;-2860361 -4522.111168,/,728.381846;-6 -3930.133160,+,2029.075972;-1901 1293.826155,-,4150.249967;-2856 2485.978772,/,-3256.632702;0 -4473.571886,-,1550.267387;-6023 772.948159,/,-4497.330379;0 4470.843583,-,-4592.121844;9062 -2308.514403,+,-1109.845068;-3418 -3900.692974,x,4862.036204;-18965310 4450.759826,-,4035.504140;415 189.460271,+,-4544.156844;-4354 3644.046577,-,453.702500;3190 -1373.240611,/,1770.743659;0 4575.444148,x,-3779.551761;-17293127 2568.090673,-,-3207.859653;5775 469.518601,-,2240.191651;-1770 -2057.096959,-,-4477.989461;2420 3204.337650,x,-1493.148109;-4784550 -3371.041505,/,-4594.887966;0 1568.390066,+,-1972.707984;-404 -2359.304028,+,-1990.550057;-4349 2804.077397,-,1490.513951;1313 3548.851595,x,3468.642823;12309698 -1143.611104,+,1052.320127;-91 3052.952747,/,-389.981377;-7 4050.861737,/,2657.979135;1 -3904.470019,/,-3794.609181;1 -2047.982229,x,-1005.110772;2058448 -4361.670468,x,2659.791667;-11601134 -3359.946238,x,-3741.311066;12570604 1724.794815,x,-744.837509;-1284691 1401.079618,x,2904.660003;4069659 -4299.371947,-,-1642.424557;-2656 1948.405591,x,4745.052729;9245287 4171.992700,-,-4687.534291;8859 -3880.964776,x,1886.857931;-7322829 -493.415791,x,624.655973;-308215 1234.500252,x,-4953.184565;-6114707 -496.104053,+,-4397.067289;-4893 1232.403448,x,716.268834;882732 335.871880,/,-1552.167678;0 -2577.279889,x,-4700.939078;12115635 4828.553239,x,2693.424473;13005343 -4030.957559,-,3859.399707;-7890 2455.563586,x,1572.847473;3862226 -774.663455,x,-2006.594987;1554435 3096.411741,/,2599.478662;1 -2212.767279,x,2445.402351;-5411106 4367.976886,/,-2566.270516;-1 4919.853371,x,380.573936;1872367 -874.443089,/,2275.103480;0 4186.314983,/,-1201.159105;-3 2742.075493,/,-2042.325265;-1 3818.176143,x,-3506.273582;-13387570 3710.418540,-,-4067.005036;7777 9.749497,-,3811.564057;-3801 -1724.042259,x,1585.044130;-2732683 -1210.739782,-,-2111.794071;901 -1819.939036,/,4310.672419;0 2324.251277,x,1801.718049;4187645 414.441692,+,-4043.936623;-3629 1081.560955,x,-1693.413103;-1831529 -800.119190,x,4929.968303;-3944562 -360.859781,-,143.208979;-504"

for i in $vals ; do
   num1=$(echo $i | cut -d';' -f1 | cut -d',' -f1)
   op=$(echo $i | cut -d';' -f1 | cut -d',' -f2)
   num2=$(echo $i | cut -d';' -f1 | cut -d',' -f3)
   answer=$(echo $i | cut -d';' -f2)
   echo "Doing $num1 $op $num2 = $answer"
   X=$(./proj2D $num1 $op $num2)
   #Y=$(printf %.03f $i)
   if [ $? -ne 0 ] ; then
       echo "PROBLEM: with $num1 $op $num2"
       echo "Your program produced a failure code with the message \"$X\" when it should not have produced a failure code.  The answer was \"$answer\""
       exit 1
   elif [ "$X" != "$answer" ] ; then
       echo "PROBLEM with $num1 $op $num2"
       echo "You have \"$X\""
       echo "But correct result is \"$answer\""
       exit 1
   fi
done

bad_vals="28a2.377236,/,4479.380015;0 -462c.030089,/,4255.262908;-1 -4277.344981,x,-d563.409090;15241929 f1327.781429,/,-626.398565;-2 -2473.734254,/,=4686.327304;0 31.038841,a,2105.965064;65366 4411.957663,++,-779.633403;3632 -2170.123012,xx,-3445.807737;7477826 2451.786791,+/,-3579.913463;0 -1023.308323,/=,-3351.643322;0 206.429845,///,-2048.938255;0 3080.300.276,x,781.843612;2408313 912.011-603,/,-3765.129223;0 -618.1.7.7340,x,2603.111812;-1609184 49ll68.184321,x,-1577.335222;-7836492 35hi46.026879,+,3490.136266;7036 -358hello2.230737,-,-2727.328379;-854 3437.480234,+,41world12.504385;7549 -3279.0after71364,x,2325.505450;-7625498 3203.321456,x,-1376.89decimal4851;-4410636 -4709.060111,enough,-3045.681811;14342298"
for i in $bad_vals ; do
   num1=$(echo $i | cut -d';' -f1 | cut -d',' -f1)
   op=$(echo $i | cut -d';' -f1 | cut -d',' -f2)
   num2=$(echo $i | cut -d';' -f1 | cut -d',' -f3)
   answer=$(echo $i | cut -d';' -f2)
   echo "Doing $num1 $op $num2 = $answer"
   X=$(./proj2D $num1 $op $num2)
   if [ $? -eq 0 ] ; then
       echo "PROBLEM: your program did not correctly detect an invalid sequence: $num1 $op $num2" 
       exit 1
   fi
done

echo "Success.  You passed all tests."
exit 0
