from flask import Flask, render_template, request, redirect, url_for, session, make_response, send_from_directory, send_file
import os
import sqlite3


app = Flask(__name__)

@app.route('/')
def send_file0():
    return send_file('login.html')

@app.route('/register.html')
def send_file1():
    return send_file('register.html')

@app.route('/profile_drive.html')
def send_file2():
    return send_file('profile_drive.html')

@app.route('/profile_operator.html')
def send_file3():
    return send_file('profile_operator.html')

@app.route('/booking.html')
def send_file4():
    return send_file('booking.html')

@app.route('/add_place.html')
def send_file5():
    return send_file('add_place.html')


@app.route('/register', methods=['POST'])
def register_user():
    try:
        data = request.get_json()
        username = data['username']
        password = data['password']
        role = data['role']
    except (TypeError, KeyError):
        return {'error': 'Invalid input data'}, 400

    connection = sqlite3.connect('mydatabase.db')
    cursor = connection.cursor()

    try:
        cursor.execute(
            'INSERT INTO users (name, password, role) VALUES (?, ?, ?)',
            (username, password, role)
        )
        connection.commit()
        return {'message': 'User registered successfully'}, 201
    except sqlite3.IntegrityError:
        return {'error': 'User already exists'}, 409
    finally:
        connection.close()

@app.route('/login', methods=['POST'])
def login_user():
    data = request.get_json()
    username = data.get('username')
    password = data.get('password')
    
    connection = sqlite3.connect('mydatabase.db')
    cursor = connection.cursor()

    try:
        cursor.execute('SELECT id, role FROM users WHERE name = ? AND password = ?', (username, password,))
        user = cursor.fetchone()

        if user is None:
            return {'error': 'Login failed'}, 401

        user_id, role = user

        response = make_response({'role': role})
        response.set_cookie('username', username)
        response.set_cookie('password', password)

        return response
    finally:
        connection.close()

@app.route('/api/getProfileData/<string:username>', methods=['GET'])
def get_profile_data(username):
    connection = sqlite3.connect('mydatabase.db')
    cursor = connection.cursor()

    cursor.execute('SELECT phone, card_data FROM users WHERE name = ?', (username,))
    user = cursor.fetchone()

    if user is None:
        return {'error': 'User not found'}, 404

    phone, card_data = user
    return {'phone': phone, 'card': card_data}, 200


@app.route('/api/getBookings/<string:username>', methods=['GET'])
def get_bookings(username):
    connection = sqlite3.connect('mydatabase.db')
    cursor = connection.cursor()

    cursor.execute('''SELECT bookings.id, places.address, places.location, places.price, users.name, bookings.start_date, bookings.end_date
                      FROM bookings
                      JOIN places ON bookings.place_id = places.id
                      JOIN users ON bookings.user_id = users.id
                      WHERE users.name = ?''', (username,))
    bookings = cursor.fetchall()

    bookings_data = [
        {
            'id': booking[0],
            'address': booking[1],
            'location': booking[2],
            'price': booking[3],
            'owner_name': booking[4],
            'start_date': booking[5],
            'end_date': booking[6]
        } for booking in bookings
    ]

    return {'bookings': bookings_data}, 200


@app.route('/api/deleteBook/<int:book_id>', methods=['DELETE'])
def delete_book(book_id):
    connection = sqlite3.connect('mydatabase.db')
    cursor = connection.cursor()

    try:
        cursor.execute('DELETE FROM bookings WHERE id = ?', (book_id,))
        if cursor.rowcount == 0:
            return {'error': 'Booking not found or not authorized'}, 404

        connection.commit()
        return '', 204
    except Exception as e:
        return {'error': str(e)}, 500
    finally:
        connection.close()


@app.route('/api/updateProfile/<string:username>', methods=['POST'])
def update_profile(username):
    data = request.get_json()
    phone = data.get('phone')
    card = data.get('card')

    connection = sqlite3.connect('mydatabase.db')
    cursor = connection.cursor()

    try:
        cursor.execute('UPDATE users SET phone = ?, card_data = ? WHERE name = ?', (phone, card, username))
        connection.commit()
        if cursor.rowcount == 0:
            return {'error': 'User not found'}, 404

        return '', 204
    except Exception as e:
        return {'error': str(e)}, 500
    finally:
        connection.close()

@app.route('/api/places', methods=['GET'])
def get_places():
    connection = sqlite3.connect('mydatabase.db')
    cursor = connection.cursor()

    try:
        cursor.execute('SELECT id, address, owner_id, price FROM places')
        places = cursor.fetchall()
        places_list = [
            {
                'id': place[0],
                'address': place[1],
                'owner_id': place[2],
                'price': place[3]
            } 
            for place in places
        ]
        return {'places': places_list}, 200
    except sqlite3.Error as e:
        return {'error': str(e)}, 500
    finally:
        connection.close()

@app.route('/api/book', methods=['POST'])
def book_place():
    data = request.get_json()
    print(f'Получены данные для бронирования: {data}')
    place_id = data.get('placeId')
    print(f'Идентификатор места: {place_id}')
    method = data.get('method')
    print(f'Метод оплаты: {method}')
    start_date = data.get('startDate')
    print(f'Дата начала: {start_date}')
    end_date = data.get('endDate')
    print(f'Дата окончания: {end_date}')
    username = data.get('username')
    print(f'Имя пользователя из сессии: {username}')

    connection = sqlite3.connect('mydatabase.db')
    cursor = connection.cursor()

    try:
        cursor.execute('SELECT id FROM places WHERE id = ?', (place_id,))
        place = cursor.fetchone()

        if place is None:
            print('Место не найдено')
            return {'error': 'Place not found'}, 404

        cursor.execute('SELECT id FROM users WHERE name = ?', (username,))
        user = cursor.fetchone()

        if user is None:
            print('Пользователь не найден')
            return {'error': 'User not found'}, 404

        user_id = user[0]
        print(f'Идентификатор пользователя: {user_id}')

        cursor.execute(
            'INSERT INTO bookings (user_id, place_id, payment_method, start_date, end_date) VALUES (?, ?, ?, ?, ?)',
            (user_id, place_id, method, start_date, end_date)
        )
        connection.commit()
        print('Бронирование успешно внесено в базу данных')

        response = make_response({'message': 'Booking successful'})
        response.status_code = 201
        response.headers['Content-Type'] = 'application/json'
        response.set_cookie('modalContent', '<h3>Покупка успешна!</h3>')
        print('Ответ успешно отправлен клиенту')
        return response
    except sqlite3.Error as e:
        print(f'Ошибка при выполнении SQL запроса: {e}')
        response = make_response({'error': str(e)})
        response.status_code = 500
        response.headers['Content-Type'] = 'application/json'
        response.set_cookie('modalContent', '<h3>Ошибка при покупке</h3>')
        return response
    finally:
        print('Закрытие соединения с базой данных')
        connection.close()
            


@app.route('/api/getPlaces/<string:username>', methods=['GET'])
def get_places_user(username):
    connection = sqlite3.connect('mydatabase.db')
    cursor = connection.cursor()

    cursor.execute('''SELECT id, address, price FROM places WHERE owner_id = 
                      (SELECT id FROM users WHERE name = ?)''', (username,))
    places = cursor.fetchall()

    places_data = [
        {
            'id': place[0],
            'address': place[1],
            'price': place[2]
        } for place in places
    ]

    connection.close()
    return places_data, 200

@app.route('/api/deletePlace/<int:place_id>', methods=['DELETE'])
def delete_place(place_id):
    connection = sqlite3.connect('mydatabase.db')
    cursor = connection.cursor()

    try:
        cursor.execute('DELETE FROM places WHERE id = ?', (place_id,))
        connection.commit()
        return {'message': 'Place deleted successfully'}, 200
    except sqlite3.Error as e:
        connection.rollback()
        return {'error': f'Error occurred: {e}'}, 500
    finally:
        connection.close()

        cursor.execute('DELETE FROM bookings WHERE id = ?', (book_id,))
        connection.commit()
        return {'success': True}, 200


@app.route('/api/add_place', methods=['POST'])
def add_place():
    data = request.get_json()
    place_name = data.get('placeName')
    address = data.get('address')
    price = data.get('price')
    username = data.get('username')

    connection = sqlite3.connect('mydatabase.db')
    cursor = connection.cursor()

    try:
        cursor.execute('SELECT id FROM users WHERE name = ?', (username,))
        user = cursor.fetchone()

        if user is None:
            return {'error': 'User not found'}, 404
        
        user_id = user[0]

        cursor.execute('INSERT INTO places (address, location, owner_id, price) VALUES (?, ?, ?, ?)', 
                       (place_name, address, user_id, price))
        connection.commit()
        return {'success': True}, 201
    except sqlite3.Error as e:
        return {'error': f'Error occurred: {e}'}, 400
    finally:
        connection.close()

@app.route('/api/downloadEx/<string:username>', methods=['GET'])
def download_ex(username):
    import csv
    from datetime import datetime
    from io import BytesIO

    connection = sqlite3.connect('mydatabase.db')
    cursor = connection.cursor()

    try:
        cursor.execute('''SELECT bookings.start_date, bookings.end_date, places.address, places.price, users.name 
                          FROM bookings
                          JOIN places ON bookings.place_id = places.id
                          JOIN users ON bookings.user_id = users.id
                          WHERE places.owner_id = (SELECT id FROM users WHERE name = ?)''', (username,))
        bookings = cursor.fetchall()

        csv_data = io.StringIO()
        csv_writer = csv.writer(csv_data)

        csv_writer.writerow(['Имя', 'Начало', 'Конец', 'Адрес', 'Цена', 'Общая Сумма'])

        total_cost = 0
        for booking in bookings:
            start_date, end_date, address, price, user_name = booking

            if not all([start_date, end_date, address, price, user_name]):
                continue

            start_date = datetime.strptime(start_date, '%Y-%m-%d')
            end_date = datetime.strptime(end_date, '%Y-%m-%d')
            total_price = (end_date - start_date).days * price
            total_cost += total_price
            csv_writer.writerow([user_name, start_date.strftime('%Y-%m-%d'), end_date.strftime('%Y-%m-%d'), address, price, total_price])

        csv_writer.writerow([])
        csv_writer.writerow(['', '', '', '', 'Итого:', total_cost])

        csv_string = csv_data.getvalue().encode('utf-8')
        response = make_response(send_file(BytesIO(csv_string),
                                           as_attachment=True,
                                           download_name='отчет.csv',
                                           mimetype='text/csv'))
    except Exception as e:
        return {'error': str(e)}, 500
    finally:
        connection.close()
    return response


def create_tables():
    connection = sqlite3.connect('mydatabase.db')
    cursor = connection.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT,
            password TEXT,
            phone TEXT,
            card_data TEXT,
            role TEXT
        )
    ''')
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS bookings (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER,
            place_id INTEGER,
            payment_method TEXT,
            start_date TEXT,
            end_date TEXT,
            FOREIGN KEY(user_id) REFERENCES users(id),
            FOREIGN KEY(place_id) REFERENCES places(id)
        )
    ''')
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS places (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            address TEXT,
            location TEXT,
            owner_id INTEGER,
            price REAL,
            FOREIGN KEY(owner_id) REFERENCES users(id)
        )
    ''')
    connection.commit()
    connection.close()
    
def print_table_data_by_column(table_name):
    connection = sqlite3.connect('mydatabase.db')
    cursor = connection.cursor()

    try:
        cursor.execute(f'SELECT * FROM {table_name}')
        columns = [description[0] for description in cursor.description]
        rows = cursor.fetchall()

        print(" | ".join(columns))
        print("-" * 50)
        for row in rows:
            print(" | ".join(map(str, row)))
    except sqlite3.Error as e:
        print(f"Error occurred: {e}")
    finally:
        connection.close()

if __name__ == '__main__':
    create_tables()
    
    print_table_data_by_column('users')
    print_table_data_by_column('bookings')
    print_table_data_by_column('places')

    app.run(host='0.0.0.0', port=5000)
    