/*Lab2 에서 두 행렬의 크기를 입력받아서 필요한 만큼의 메모리를 동적으로 할당하여 
행렬의 내용을 저장하고 두 행렬을 더하는 프로그램을 Rust 의 Vec<T> 자료형을 를 활용하여 구현하시오.*/

use std::io;

fn main() {
    let mut input = String::new();
    println!("행렬의 행과 열의 크기를 입력하세요 (예: 2 3):");

    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read line");

    // 입력받은 문자열을 공백 기준으로 분리하여 숫자로 변환
    let parts: Vec<&str> = input.trim().split_whitespace().collect();

    //두 행렬의 행, 열 크기
    let rows: usize = parts[0].parse().expect("Please enter a valid number for rows"); 
    let cols: usize = parts[1].parse().expect("Please enter a valid number for columns");

    let mut matrix1: Vec<Vec<i32>> = Vec::new();
    let mut matrix2: Vec<Vec<i32>> = Vec::new();

    let mut result_matrix: Vec<Vec<i32>> = Vec::new();
    
    println!("첫 번째 행렬을 입력하세요:");
    for i in 0..rows { //행의 수만큼 입력 받는다.
        let mut row = Vec::new();
        println!("{}번째 행을 입력하세요 (예: 2 3):", i + 1);

        let mut row_input = String::new();
        io::stdin()
            .read_line(&mut row_input)
            .expect("Failed to read line");

        let row_values: Vec<i32> = row_input
            .trim() //입력받은 문자열 양옆의 공백을 제거
            .split_whitespace() // 공백으로 분리된 문자열을 Iterator로 만듦
            .map(|s| s.parse().expect("Invalid number")) // 각 요소를 정수로 변환
            .collect(); // 최종적으로 Vec<i32>로 수집

        row.extend(row_values);
        matrix1.push(row);
    }
    println!("두 번째 행렬을 입력하세요:");
    for i in 0..rows {
        let mut row = Vec::new();
        println!("{}번째 행을 입력하세요 (예: 2 3):", i + 1);
        let mut row_input = String::new();
        io::stdin()
            .read_line(&mut row_input)
            .expect("Failed to read line");

        let row_values: Vec<i32> = row_input
            .trim()
            .split_whitespace()
            .map(|s| s.parse().expect("Invalid number"))
            .collect();
        row.extend(row_values);
        matrix2.push(row);
    }

    for i in 0..rows {
        let mut row = Vec::new();
        for j in 0..cols {
            let sum = matrix1[i][j] + matrix2[i][j];
            row.push(sum);
        }
        result_matrix.push(row);
    }
    println!("두 행렬의 합:");
    for row in result_matrix {
        for value in row {
            print!("{} ", value);
        }
        println!();
    }
}
