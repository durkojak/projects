import './App.css';
import React from "react";
import { Route, Routes, BrowserRouter} from "react-router-dom";
import LoginPage  from "./pages/LoginPage.tsx";
import MoviePage from "./pages/MoviePage.tsx";
import AdminPage from "./pages/AdminPage.tsx";

const App: React.FC = () => {
    return (
        <BrowserRouter>
                <Routes>
                    <Route path="/" element={<LoginPage />} />
                    <Route path="/movies" element={<MoviePage />} />
                    <Route path="/admin" element={<AdminPage />} />
                    <Route path="*" element={<div>404 - Page Not Found</div>} />
                </Routes>
        </BrowserRouter>
    );
};

export default App
