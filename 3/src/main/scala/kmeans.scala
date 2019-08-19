import java.io.File
import breeze.linalg.{Vector, DenseVector, DenseMatrix, norm, squaredDistance, csvwrite}
import breeze.linalg.functions.{cosineDistance}
import org.apache.spark._

object SparkKMeans {

	val sparkConf = new SparkConf().setAppName("SparkKMeans")
	val sc = new SparkContext(sparkConf)

	/* 
		Function to read dataset and create RDD
		filename: file path
		n: number of cores / RDD slices
	*/
	def parse_vector(filename: String, n: Int) = {
		val lines = sc.textFile(filename, n - 1)
		val data = lines.map(l => 
			Vector(l.split(',').map(_.toDouble))
		).cache()
		data
	}

	/*
		Function to compute Cosine Similarity
		x, y: Vectors to compute similarity
	*/
  def cosineSimilarity(x: Vector[Double], y: Vector[Double]): Double = {
  	val denom = norm(x) * norm(y)
    val dotProduct = x dot y
    if (denom == 0.0) {
      0.0
    } else {
      dotProduct / denom
    }
  }
	
	/* 
		Find the closest point 
		p: Vector. Point to evaluate
		centers: Array of vectors. Actual centers
	*/
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

	/*
		Function to save centroids and number of iterations
	*/
	def saveExperiment(seed: Long, k: Int, iter: Int, kPoints: Array[Vector[Double]]) = {
		val file = new File(s"data/output/${k}/${seed}.txt")
		//val mat = DenseMatrix.zeros[Double](k+1, 7604)
		val mat = DenseMatrix.zeros[Double](k+1, 3754)
		mat(0, 0) = iter
		for (i <- 0 until k) {
			//mat(i+1, 0 to 7603) := kPoints(i).t
			mat(i+1, 0 to 3753) := kPoints(i).t
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
		var iter = 0 // To count iterations
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
		}
		println(s"Iterations: ${iter}")

		saveExperiment(seed, k, iter, kPoints)
		
		sc.stop()
	}
}