import React, { useState } from "react";
import { useNavigate } from "react-router-dom";
import api from "../api/api.tsx";
import '../styles/LoginPage.css';  // Import the custom CSS file

const LoginPage: React.FC = () => {
    const [userID, setUserID] = useState('');
    const [password, setPassword] = useState('');
    const navigate = useNavigate();
    const [newUserID, setNewUserID] = useState('');
    const [age, setAge] = useState('');
    const [gender, setGender] = useState('');
    const [occupation, setOccupation] = useState('');
    const [zipCode, setZipCode] = useState('');

    const handleLogin = async (e: React.FormEvent) => {
        e.preventDefault();
        localStorage.removeItem('userId')

        if (userID && password) {
            try {
                const response = await api.get(`/user/${userID}/exists`);

                if (!response.data.exists) {
                    alert("This user doesn't exist.");
                    return;
                }

                localStorage.setItem('userId', userID.toString());
                navigate('/movies');
            } catch (error) {
                alert("This user doesn't exist.");
                console.error(error);
            }
        }
    };

    const handleRegister = async () => {
        if (newUserID && age && gender && occupation && zipCode) {
            try {
                const response = await api.post(`/user/register`, {
                    id: parseInt(newUserID),
                    age: parseInt(age),
                    gender,
                    occupation,
                    zip_code: zipCode
                });

                if (response.status === 201) {
                    alert(`User '${newUserID}' registered successfully!`);
                    setNewUserID('');
                    setAge('');
                    setGender('');
                    setOccupation('');
                    setZipCode('');
                } else {
                    alert("Registration failed.");
                }
            } catch (error: any) {
                if (error.response?.status === 409) {
                    alert("User already exists.");
                } else {
                    alert("Error registering user.");
                }
                console.error(error);
            }
        } else {
            alert("Please fill out all fields.");
        }
    };

    // Admin button functionality
    const handleAdminAccess = () => {
        navigate('/admin');
    };

    return (
        <div className="login-container">
            <h1 className="login-title">Login</h1>
            <form onSubmit={handleLogin} className="login-form">
                <div className="form-group">
                    <input
                        type="text"
                        placeholder="UserID"
                        value={userID}
                        onChange={(e) => setUserID(e.target.value)}
                        className="input-field"
                    />
                </div>
                <div className="form-group">
                    <input
                        type="password"
                        placeholder="Password"
                        value={password}
                        onChange={(e) => setPassword(e.target.value)}
                        className="input-field"
                    />
                </div>
                <button type="submit" className="submit-btn">Login</button>
            </form>

            <h2>Register</h2>
            <form onSubmit={(e) => {
                e.preventDefault();
                handleRegister();
            }} className="register-form">
                <div className="form-group">
                    <input
                        type="number"
                        placeholder="User ID"
                        value={newUserID}
                        onChange={(e) => setNewUserID(e.target.value)}
                        className="input-field"
                    />
                </div>
                <div className="form-group">
                    <input
                        type="number"
                        placeholder="Age"
                        value={age}
                        onChange={(e) => setAge(e.target.value)}
                        className="input-field"
                    />
                </div>
                <div className="form-group">
                    <input
                        type="text"
                        placeholder="Gender"
                        value={gender}
                        onChange={(e) => setGender(e.target.value)}
                        className="input-field"
                    />
                </div>
                <div className="form-group">
                    <input
                        type="text"
                        placeholder="Occupation"
                        value={occupation}
                        onChange={(e) => setOccupation(e.target.value)}
                        className="input-field"
                    />
                </div>
                <div className="form-group">
                    <input
                        type="text"
                        placeholder="Zip Code"
                        value={zipCode}
                        onChange={(e) => setZipCode(e.target.value)}
                        className="input-field"
                    />
                </div>
                <button type="submit" className="submit-btn">Register</button>
            </form>

            {/* Admin Button */}
            <button
                onClick={handleAdminAccess}
                className="admin-btn"
            >
                Admin Access
            </button>
        </div>
    );
};

export default LoginPage;
