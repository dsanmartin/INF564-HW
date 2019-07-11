spark-submit \
	--class "SparkKMeans" \
	--master local[4] \
	--driver-cores 2 \
	target/scala-2.11/kmeans_2.11-1.0.jar $1 $2 $3
	# --deploy-mode client \
	# --conf spark.executor.extraJavaOptions='-Dlog4j.configuration=log4j.properties' \
	# --driver-java-options -Dlog4j.configuration=src/main/config/log4j.properties \
	# --files src/main/resources/log4j.properties \
	#--driver-java-options "-Dlog4j.debug=false -Dlog4j.configuration=src/main/resources/log4j.properties" \
	#--conf "spark.executor.extraJavaOptions=-Dlog4j.debug=false -Dlog4j.configuration=src/main/resources/log4j.properties" \
	
	
