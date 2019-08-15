import java.io.File
import breeze.linalg.{Vector, DenseVector, DenseMatrix, norm, squaredDistance, csvwrite}
import breeze.linalg.functions.{cosineDistance}
import org.apache.spark._
//import org.apache.log4j.{Level, Logger}


object SparkKMeans {

	val sparkConf = new SparkConf().setAppName("SparkKMeans")
	val sc = new SparkContext(sparkConf)

	def splitVector(line: String): Vector[Double] = {
	  DenseVector(line.split(',').map(_.toDouble))
	}

	def parse_vector(filename: String, n: Int) = {
		val lines = sc.textFile(filename, n - 1)
		val data = lines.map(splitVector _).cache()
		data
	}

  def cosineSimilarity(x: Vector[Double], y: Vector[Double]): Double = {
  	// (x dot y) / (norm(x) * norm(y))
  	val denom = norm(x) * norm(y)
    val dotProduct = x.dot(y)//dot(x, y)
    if (denom == 0.0) {
      0.0
    } else {
      dotProduct / denom
    }
  }

	def closestPoint(p: Vector[Double], centers: Array[Vector[Double]]): Int = {
	  var bestIndex = 0
	  var closest = Double.PositiveInfinity
	  for (i <- 0 until centers.length) {
	    //val tempDist = squaredDistance(p, centers(i))
	    val tempDist = cosineDistance(p, centers(i))
	    if (tempDist < closest) {
	      closest = tempDist
	      bestIndex = i
	    }	
	  }
	  bestIndex
	}

	def saveExperiment(seed: Long, k: Int, iter: Int, kPoints: Array[Vector[Double]]) = {
		val file = new File(s"data/output/${k}/${seed}.txt")
		val mat = DenseMatrix.zeros[Double](k+1, 7604)
		mat(0, 0) = iter
		for (i <- 0 until k) {
			//csvwrite(file, new DenseMatrix(1, 3, kPoints(i).toArray), separator = ',')
			mat(i+1, 0 to 7603) := kPoints(i).t//.toArray
		}
		csvwrite(file, mat, separator = ',')
	}

	def main(args: Array[String]) {
		val n = 4 // Number of cores
		val data = parse_vector(args(0), n)
		val k = args(1).toInt // K prototipos
		val convergeDist = args(2).toDouble
		val seed = System.currentTimeMillis
		val kPoints = data.takeSample(withReplacement=false, k, seed).toArray
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
				//tempDist += squaredDistance(kPoints(i), newPoints(i))
				tempDist += cosineDistance(kPoints(i), newPoints(i))
			}
			for (newP <- newPoints) kPoints(newP._1) = newP._2
			iter += 1
			println(s"Iterations: ${iter}")
		}
		println(s"Iterations: ${iter}")

		saveExperiment(seed, k, iter, kPoints)
		
		sc.stop()
	}
}