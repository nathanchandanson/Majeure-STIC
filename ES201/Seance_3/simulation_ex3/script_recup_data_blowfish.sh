

echo "Study the impact of the number of UF on blowfish with in-order execution" > result_bf_inorder.txt
echo "SIZE;N_UF;nb_cycles;CPI" >> result_bf_inorder.txt
echo "Study the impact of the number of UF on blowfish with out-of-order execution" > result_bf_out-of-order.txt
echo "SIZE;N_UF;nb_cycles;CPI" >> result_bf_out-of-order.txt

for SIZE in small medium large
do
	for UF in 1 2 4 8
	do
		FILEIO="simu/sim_bf_enc_order_${SIZE}_M${UF}"
		FILEO3="simu/sim_bf_enc_o3_${SIZE}_M${UF}"
		LINEIO="${SIZE};${UF}"
		LINEO3="${SIZE};${UF}"
		if [ ! -s $FILEIO ]; then
			echo "No such file $FILEIO"
			exit
		fi
		if [ ! -s $FILEO3 ]; then
			echo "No such file $FILEO3"
			exit
		fi
		for D in sim_cycle sim_CPI 
		do
			LINEIO+=";`grep ${D} $FILEIO | cut -d# -f1 | sed -e "s/[a-z._]*${D}//g" -e "s/ //g"`"
			LINEO3+=";`grep ${D} $FILEO3 | cut -d# -f1 | sed -e "s/[a-z._]*${D}//g" -e "s/ //g"`"
		done
		echo $LINEIO >> result_bf_inorder.txt
		echo $LINEO3 >> result_bf_out-of-order.txt
	done
done





