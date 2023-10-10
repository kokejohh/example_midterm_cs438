import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Arrays;

public class ass3_server implements ass3_interface {
	public ass3_server() {}

	public int[] sortArray(int[] arr) {
		Arrays.sort(arr);
		return arr;
	}

	public static void main(String args[]) {
		try {
			ass3_server obj = new ass3_server();
			ass3_interface stub = (ass3_interface)UnicastRemoteObject.exportObject(obj, 0);
			
			Registry registry = LocateRegistry.getRegistry();
			registry.bind("Assign3", stub);

			System.out.println("Server ready");
		} catch (Exception e) {
			System.err.println("Server exception: " + e.toString());
			e.printStackTrace();
		}
	}
}
