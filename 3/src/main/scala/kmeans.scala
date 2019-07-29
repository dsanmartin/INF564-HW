import java.io.File
import breeze.linalg.{Vector, DenseVector, squaredDistance, csvwrite}
import org.apache.spark._
import org.apache.log4j.{Level, Logger}

object SparkKMeans {

	def parseVector(line: String): Vector[Double] = {
	  DenseVector(line.split(',').map(_.toDouble))
	}

	def closestPoint(p: Vector[Double], centers: Array[Vector[Double]]): Int = {
	  var bestIndex = 0
	  var closest = Double.PositiveInfinity
	  for (i <- 0 until centers.length) {
	    val tempDist = squaredDistance(p, centers(i))
	    if (tempDist < closest) {
	      closest = tempDist
	      bestIndex = i
	    }
	  }
	  bestIndex
	}

	def main(args: Array[String]) {
		val sparkConf = new SparkConf().setAppName("SparkKMeans")
		val sc = new SparkContext(sparkConf)
		val n = 4 // Number of cores
		val lines = sc.textFile(args(0), n - 1)
		val data = lines.map(parseVector _).cache()
		val k = args(1).toInt // K prototipos
		val convergeDist = args(2).toDouble
		val kPoints = data.takeSample(withReplacement=false, k, System.currentTimeMillis).toArray
		var tempDist = 1.0	
		var iter = 0
		while (tempDist > convergeDist) {
			val closest = data.map(p => (closestPoint(p, kPoints), (p, 1))) // closestPoint id_centroide | (p, 1) el 1 es para conteo
			val pointStats = closest.reduceByKey{ case ((p1, c1), (p2, c2)) => (p1 + p2, c1 + c2) } // <c_id, [(p1, 1), (p2, 1), ...]>
			val newPoints = pointStats.map{ pair =>
				(pair._1, pair._2._1 * (1.0 / pair._2._2)) // pair._1 indice, pair._2._1  \sum_{p\in Centroide} p_i ._1 es el valor | pair._2._2 numero de puntos de cluster
			}.collectAsMap()
			tempDist = 0.0
			for (i <- 0 until k) {
				tempDist += squaredDistance(kPoints(i), newPoints(i))
			}
			for (newP <- newPoints) kPoints(newP._1) = newP._2
			iter += 1
		}
		println(s"Iterations: ${iter}")
		// println(s"Centroids:")
		// for (i <- 0 until k) {
		// 	println(s"${kPoints(i)}")
		// }
		//csvwrite(new File("text.txt"), kPoints.toArray, separator = ',')
		sc.stop()
	}
}