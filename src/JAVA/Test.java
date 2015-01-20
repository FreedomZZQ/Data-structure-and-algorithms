
public class Test {
	public static int binarySearch(int key, int[] a){
		int l = 0;
		int r = a.length - 1;
		while(l <=  r){
			int mid = (l + r) / 2;
			if(key < a[mid]) r = mid - 1;
			else if(key > a[mid]) l = mid + 1;
			else return mid;
		}
		return -1;
	}
	public static int gcd(int p, int q){
		System.out.println(p + " " + q);
		if(q == 0) return p;
		int r = p % q;
		return gcd(q, r);
	}
	//牛顿迭代法求平方根
	public static double sqrt(double c){
		if(c < 0) return Double.NaN;
		double err = 1e-15;
		double t = c;
		while(Math.abs(t - c/t) > err * t)
			t = (c/t + t) /2.0;
		return t;
	}
	//计算调和级数
	public static double H(int N){
		double sum = 0.0;
		for(int i = 1;i <= N;i++)
			sum += 1.0/i;
		return sum;
	}
	public static void main(String []args){
		int x = 1111111;
		int y = 1234567;
		System.out.println(gcd(x, y));
	}
}
 