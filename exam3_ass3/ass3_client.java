import java.io.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class ass3_client {
	private ass3_client() {}

	public static void main(String[] args) {
		String host = (args.length < 1) ? null : args[0];

		try {
			Registry registry = LocateRegistry.getRegistry(host);

			ass3_interface stub = (ass3_interface) registry.lookup("Assign3");
			Scanner scan = new Scanner(System.in);

			System.out.println("Enter number of arrays: ");
			int[] nums = new int[scan.nextInt()];
			for (int i = 0; i < nums.length; i++) {
				System.out.print("Enter number " + (i + 1) + ": ");
				nums[i] = scan.nextInt();
			}

			nums = stub.sortArray(nums);

			System.out.print("From Server: ");
			for (int i = 0; i < nums.length; i++) {
				System.out.print(nums[i] + " ");
			}
			System.out.println();
		} catch (Exception e) {
			System.err.println("Client exception: " + e.toString());
			e.printStackTrace();
		}
	}
}
