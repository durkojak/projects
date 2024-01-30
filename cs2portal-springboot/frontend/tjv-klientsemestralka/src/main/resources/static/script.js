//// PLAYERS

async function fetchPlayers() {
    try {
        const response = await fetch('http://localhost:8080/player', {
            method: 'GET'
        });
        const data = await response.json();
        populatePlayerTable(data);
    } catch (error) {
        console.error('Error fetching data:', error);
    }
}

async function deletePlayer(playerId) {
    try {
        const response = await fetch(`http://localhost:8080/player/${playerId}`, {
            method: 'DELETE',
        });

        if (!response.ok) {
            throw new Error(`Failed to delete player. Status: ${response.status}`);
        }

        console.log('Player deleted');

        fetchPlayers();
    } catch (error) {
        console.error('Error deleting player:', error);
    }
}

async function addPlayer(playerData) {
    try {
        const response = await fetch('http://localhost:8080/player', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(playerData),
        });

        if (!response.ok) {
            throw new Error(`Failed to add player. Status: ${response.status}`);
        }

        const addedPlayer = await response.json();
        console.log('Player added successfully:', addedPlayer);

        fetchPlayers();
    } catch (error) {
        console.error('Error adding player:', error);
    }
}

async function editPlayer(playerId) {
    try {
        const response = await fetch(`http://localhost:8080/player/${playerId}`, {
            method: 'GET',
        });

        if (!response.ok) {
            throw new Error(`Failed to fetch player. Status: ${response.status}`);
        }

        const playerData = await response.json();


        populateEditForm(playerData, playerId);
    } catch (error) {
        console.error('Error fetching player data:', error);
    }
}

function populateEditForm(playerData, playerId) {

    document.getElementById('editPlayerId').value = playerId;
    document.getElementById('editNickname').value = playerData.nickname;
    document.getElementById('editKdRatio').value = playerData.kdRatio;
    document.getElementById('editFavGun').value = playerData.favGun;


    document.getElementById('editPlayerForm').style.display = 'block';
}

document.getElementById('editPlayerSubmit').addEventListener('click', function () {

    const editedPlayerData = {
        id: document.getElementById('editPlayerId').value,
        nickname: document.getElementById('editNickname').value,
        kdRatio: parseFloat(document.getElementById('editKdRatio').value),
        favGun: document.getElementById('editFavGun').value,

    };


    updatePlayer(editedPlayerData.id, editedPlayerData);


    document.getElementById('editPlayerForm').style.display = 'none';
});

async function updatePlayer(playerId, editedPlayerData) {
    try {
        const response = await fetch(`http://localhost:8080/player/${playerId}`, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(editedPlayerData),
        });

        if (!response.ok) {
            throw new Error(`Failed to update player. Status: ${response.status}`);
        }

        console.log('Player updated successfully');


        fetchPlayers();
    } catch (error) {
        console.error('Error updating player:',
            error);
    }
}

function populatePlayerTable(players) {

    const tableBody = document.querySelector("#playerTable tbody");


    tableBody.innerHTML = '';


    players.forEach(player => {
        const row = document.createElement('tr');


        const idCell = document.createElement('td');
        idCell.textContent = player.idPlayer;
        row.appendChild(idCell);


        const nicknameCell = document.createElement('td');
        nicknameCell.textContent = player.nickname;
        row.appendChild(nicknameCell);


        const kdRatioCell = document.createElement('td');
        kdRatioCell.textContent = player.kdRatio;
        row.appendChild(kdRatioCell);


        const favGunCell = document.createElement('td');
        favGunCell.textContent = player.favGun;
        row.appendChild(favGunCell);

        const teamCell = document.createElement('td');
        if (player.memberOf) {
            teamCell.textContent = player.memberOf.teamName;
        } else {
            teamCell.textContent = "N/A";
        }

        row.appendChild(teamCell);


        const deleteCell = document.createElement('td');
        const deleteButton = document.createElement('button');
        deleteButton.textContent = 'Delete';
        deleteButton.addEventListener('click', () => deletePlayer(player.idPlayer));
        deleteCell.appendChild(deleteButton);
        row.appendChild(deleteCell);


        const editCell = document.createElement('td');
        const editButton = document.createElement('button');
        editButton.textContent = 'Edit';
        editButton.addEventListener('click', () => editPlayer(player.idPlayer));
        editCell.appendChild(editButton);
        row.appendChild(editCell);


        tableBody.appendChild(row);
    });
}

document.getElementById('addPlayerForm').addEventListener('submit', function (event) {
    event.preventDefault();

    const nickname = document.getElementById('nickname').value;
    const kdRatio = parseFloat(document.getElementById('kdRatio').value);
    const favGun = document.getElementById('favGun').value;



    const newPlayerData = {
        nickname: nickname,
        kdRatio: kdRatio,
        favGun: favGun,

    };

    addPlayer(newPlayerData);


    this.reset();
});

//// TEAMS

async function fetchTeams() {
    try {
        const response = await fetch('http://localhost:8080/team', {
            method: 'GET'
        });
        const data = await response.json();
        // Call a function to update the table with the fetched data
        populateTeamTable(data);
    } catch (error) {
        console.error('Error fetching data:', error);
    }
}


function populateTeamTable(teams) {

    const tableBody = document.querySelector("#teamTable tbody");


    tableBody.innerHTML = '';


    teams.forEach(team => {
        const row = document.createElement('tr');


        const idCell = document.createElement('td');
        idCell.textContent = team.idTeam;
        row.appendChild(idCell);


        const teamNameCell = document.createElement('td');
        teamNameCell.textContent = team.teamName;
        row.appendChild(teamNameCell);


        const globalRankingCell = document.createElement('td');
        globalRankingCell.textContent = team.globalRanking;
        row.appendChild(globalRankingCell);


        const languageTeamCell = document.createElement('td');
        languageTeamCell.textContent = team.languageTeam;
        row.appendChild(languageTeamCell);



        const membersCell = document.createElement('td');
        if (team.rosterOfTeam && team.rosterOfTeam.length > 0) {

            team.rosterOfTeam.forEach(player => {
                const memberInfo = document.createElement('div');
                memberInfo.textContent = `${player.nickname}`;
                membersCell.appendChild(memberInfo);
            });
        } else {
            membersCell.textContent = "N/A";
        }

        row.appendChild(membersCell);


        const deleteCell = document.createElement('td');
        const deleteButton = document.createElement('button');
        deleteButton.textContent = 'Delete';
        deleteButton.addEventListener('click', function () {

            deleteTeam(team.idTeam);
            row.remove();
        });
        deleteCell.appendChild(deleteButton);
        row.appendChild(deleteCell);





        const editCell = document.createElement('td');
        const editButton = document.createElement('button');
        editButton.textContent = 'Edit';
        editButton.addEventListener('click', () => editTeam(team.idTeam));
        editCell.appendChild(editButton);
        row.appendChild(editCell);


        tableBody.appendChild(row);
    });
}

async function deleteTeam(teamId) {
    try {
        const response = await fetch(`http://localhost:8080/team/${teamId}`, {
            method: 'DELETE',
        });

        if (!response.ok) {
            throw new Error(`Failed to delete team. Status: ${response.status}`);
        }

        console.log('Team deleted successfully');


        fetchTeams();
    } catch (error) {
        console.error('Error deleting team:', error);
    }
}

document.getElementById('addTeamForm').addEventListener('submit', function (event) {
    event.preventDefault();

    const teamName = document.getElementById('teamName').value;
    const globalRanking = parseFloat(document.getElementById('globalRanking').value);
    const languageTeam = document.getElementById('languageTeam').value;



    const newTeamData = {
        teamName: teamName,
        globalRanking: globalRanking,
        languageTeam: languageTeam,

    };

    addTeam(newTeamData);


    this.reset();
});


async function addTeam(teamData) {
    try {
        const response = await fetch('http://localhost:8080/team', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(teamData),
        });

        if (!response.ok) {
            throw new Error(`Failed to add team. Status: ${response.status}`);
        }

        const addedTeam = await response.json();
        console.log('Player added successfully:', addedTeam);


        fetchTeams();
    } catch (error) {
        console.error('Error adding team:', error);
    }
}


async function editTeam(teamId) {
    try {
        const response = await fetch(`http://localhost:8080/team/${teamId}`, {
            method: 'GET',
        });

        if (!response.ok) {
            throw new Error(`Failed to fetch team. Status: ${response.status}`);
        }

        const teamData = await response.json();


        populateTeamEditForm(teamData, teamId);
    } catch (error) {
        console.error('Error fetching team data:', error);
    }
}

function populateTeamEditForm(teamData, teamId) {
    document.getElementById('editTeamId').value = teamId;
    document.getElementById('editTeamName').value = teamData.teamName;
    document.getElementById('editGlobalRanking').value = teamData.globalRanking;
    document.getElementById('editLanguageTeam').value = teamData.languageTeam;


    document.getElementById('editTeamForm').style.display = 'block';
}

document.getElementById('editTeamSubmit').addEventListener('click', function () {
    const editedTeamData = {
        id: document.getElementById('editTeamId').value,
        teamName: document.getElementById('editTeamName').value,
        globalRanking: parseFloat(document.getElementById('editGlobalRanking').value),
        languageTeam: document.getElementById('editLanguageTeam').value,
    };


    updateTeam(editedTeamData.id, editedTeamData);


    document.getElementById('editTeamForm').style.display = 'none';
});

async function updateTeam(teamId, editedTeamData) {
    try {
        const response = await fetch(`http://localhost:8080/team/${teamId}`, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(editedTeamData),
        });

        if (!response.ok) {
            throw new Error(`Failed to update team. Status: ${response.status}`);
        }

        console.log('Team updated successfully');

        // Optionally, you can update the table with the new data
        fetchTeams();
    } catch (error) {
        console.error('Error updating team:',
            error);
    }
}

//// TOURNAMENTS
async function editTournament(tournamentId) {
    try {
        const response = await fetch(`http://localhost:8080/tournament/${tournamentId}`, {
            method: 'GET',
        });

        if (!response.ok) {
            throw new Error(`Failed to fetch tournament. Status: ${response.status}`);
        }

        const tournamentData = await response.json();


        populateTournamentEditForm(tournamentData, tournamentId);
    } catch (error) {
        console.error('Error fetching tournament data:', error);
    }
}

function populateTournamentEditForm(tournamentData, tournamentId) {

    document.getElementById('editTournamentId').value = tournamentId;
    document.getElementById('editTournamentName').value = tournamentData.tournamentName;
    document.getElementById('editPrizePool').value = tournamentData.prizePool;
    document.getElementById('editLocation').value = tournamentData.location;


    document.getElementById('editTournamentForm').style.display = 'block';
}

document.getElementById('editTournamentSubmit').addEventListener('click', function () {

    const editedTournamentdata = {
        id: document.getElementById('editTournamentId').value,
        tournamentName: document.getElementById('editTournamentName').value,
        prizePool: parseFloat(document.getElementById('editPrizePool').value),
        location: document.getElementById('editLocation').value,

    };


    updateTournament(editedTournamentdata.id, editedTournamentdata);


    document.getElementById('editTournamentForm').style.display = 'none';
});

async function updateTournament(tournamentId, editedTournamentdata) {
    try {
        const response = await fetch(`http://localhost:8080/tournament/${tournamentId}`, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(editedTournamentdata),
        });

        if (!response.ok) {
            throw new Error(`Failed to update tournament. Status: ${response.status}`);
        }

        console.log('Tournament updated successfully');


        fetchTournaments();
    } catch (error) {
        console.error('Error updating tournament:',
            error);
    }
}


document.getElementById('addTournamentForm').addEventListener('submit', function (event) {
    event.preventDefault();

    const tournamentName = document.getElementById('tournamentName').value;
    const prizePool = parseFloat(document.getElementById('prizePool').value);
    const location = document.getElementById('location').value;



    const newTournamentData = {
        tournamentName: tournamentName,
        prizePool: prizePool,
        location: location,

    };

    addTournament(newTournamentData);


    this.reset();
});


async function addTournament(tournamentData) {
    try {
        const response = await fetch('http://localhost:8080/tournament', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(tournamentData),
        });

        if (!response.ok) {
            throw new Error(`Failed to add tournament. Status: ${response.status}`);
        }

        const addedTournament = await response.json();
        console.log('Tournament added successfully:', addedTournament);


        fetchTournaments();
    } catch (error) {
        console.error('Error adding tournament:', error);
    }
}


async function fetchTournaments() {
    try {
        const response = await fetch('http://localhost:8080/tournament', {
            method: 'GET'
        });
        const data = await response.json();

        populateTournamentTable(data);
    } catch (error) {
        console.error('Error fetching data:', error);
    }
}

function populateTournamentTable(tournaments) {

    const tableBody = document.querySelector("#tournamentTable tbody");


    tableBody.innerHTML = '';


    tournaments.forEach(tournament => {
        const row = document.createElement('tr');


        const idCell = document.createElement('td');
        idCell.textContent = tournament.idTournament;
        row.appendChild(idCell);


        const tournamentNameCell = document.createElement('td');
        tournamentNameCell.textContent = tournament.tournamentName;
        row.appendChild(tournamentNameCell);


        const prizePoolCell = document.createElement('td');
        prizePoolCell.textContent = tournament.prizePool;
        row.appendChild(prizePoolCell);

        const teamsCell = document.createElement('td');

        if (tournament.teamsParticipating && tournament.teamsParticipating.length > 0) {

            tournament.teamsParticipating.forEach(team => {
                const teamInfo = document.createElement('div');
                teamInfo.textContent = `${team.teamName}`;
                teamsCell.appendChild(teamInfo);
            });
        } else {
            teamsCell.textContent = "N/A";
        }

        row.appendChild(teamsCell);

        const deleteCell = document.createElement('td');
        const deleteButton = document.createElement('button');
        deleteButton.textContent = 'Delete';
        deleteButton.addEventListener('click', function () {

            deleteTournament(tournament.idTournament);

            row.remove();
        });
        deleteCell.appendChild(deleteButton);
        row.appendChild(deleteCell);


        const editCell = document.createElement('td');
        const editButton = document.createElement('button');
        editButton.textContent = 'Edit';
        editButton.addEventListener('click', () => editTournament(tournament.idTournament));
        editCell.appendChild(editButton);
        row.appendChild(editCell);


        tableBody.appendChild(row);
    });
}


async function deleteTournament(tournamentId) {
    try {
        const response = await fetch(`http://localhost:8080/tournament/${tournamentId}`, {
            method: 'DELETE',
        });

        if (!response.ok) {
            throw new Error(`Failed to delete tournament. Status: ${response.status}`);
        }

        console.log('Tournament deleted successfully with id', tournamentId);


        fetchTournaments();
    } catch (error) {
        console.error('Error deleting tournament:', error);
    }
}


document.addEventListener("DOMContentLoaded", function () {

    var addPlayerForm = document.getElementById("addPlayerForm");
    var addTeamForm = document.getElementById("addTeamForm");
    var addTournamentForm = document.getElementById("addTournamentForm");
    var editPlayerForm = document.getElementById("editPlayerForm");
    var editTeamForm = document.getElementById("editTeamForm");
    var editTournamentForm = document.getElementById("editTournamentForm");
    var playerTable = document.getElementById("playerTable");
    var teamTable = document.getElementById("teamTable");
    var tournamentTable = document.getElementById("tournamentTable");


    addPlayerForm.style.display = "none";
    editPlayerForm.style.display = "none";


    function toggleContent(tableToShow) {
        if (tableToShow === "playerTable") {
            addPlayerForm.style.display = "block";
            editPlayerForm.style.display = "block";
            addTeamForm.style.display = "none";
            editTeamForm.style.display = "none";
            addTournamentForm.style.display = "none";
            editTournamentForm.style.display = "none";
            playerTable.style.display = "table";
            teamTable.style.display = "none";
            tournamentTable.style.display = "none";
            document.getElementById("tableTitle").textContent = "Players";
        } else if (tableToShow === "teamTable") {
            addPlayerForm.style.display = "none";
            editPlayerForm.style.display = "none";
            addTeamForm.style.display = "block";
            editTeamForm.style.display = "block";
            addTournamentForm.style.display = "none";
            editTournamentForm.style.display = "none";
            playerTable.style.display = "none";
            teamTable.style.display = "table";
            tournamentTable.style.display = "none";
            document.getElementById("tableTitle").textContent = "Teams";
        } else if (tableToShow === "tournamentTable") {
            addPlayerForm.style.display = "none";
            editPlayerForm.style.display = "none";
            addTeamForm.style.display = "none";
            editTeamForm.style.display = "none";
            addTournamentForm.style.display = "block";
            editTournamentForm.style.display = "block";
            playerTable.style.display = "none";
            teamTable.style.display = "none";
            tournamentTable.style.display = "table";
            document.getElementById("tableTitle").textContent = "Tournaments";
        }
    }


    document.getElementById("showPlayerTable").addEventListener("click", function () {
        toggleContent("playerTable");
    });

    document.getElementById("showTeamTable").addEventListener("click", function () {
        toggleContent("teamTable");
    });

    document.getElementById("showTournamentTable").addEventListener("click", function () {
        toggleContent("tournamentTable");
    });


    toggleContent("playerTable");
});


//// BUTTONS
document.getElementById('showPlayerTable').addEventListener('click', function () {
    document.getElementById('playerTable').style.display = 'table';
    document.getElementById('teamTable').style.display = 'none';
    document.getElementById('tournamentTable').style.display = 'none';
    document.getElementById('tableTitle').textContent = 'Players';
});

document.getElementById('showTeamTable').addEventListener('click', function () {
    document.getElementById('playerTable').style.display = 'none';
    document.getElementById('teamTable').style.display = 'table';
    document.getElementById('tournamentTable').style.display = 'none';
    document.getElementById('tableTitle').textContent = 'Teams';
});

document.getElementById('showTournamentTable').addEventListener('click', function () {
    document.getElementById('playerTable').style.display = 'none';
    document.getElementById('teamTable').style.display = 'none';
    document.getElementById('tournamentTable').style.display = 'table';
    document.getElementById('tableTitle').textContent = 'Tournaments';
});


//// BUSINESS OPERACE

async function getTeamInfo(teamId) {
    try {
        const response = await fetch(`http://localhost:8080/team/${teamId}`, {
            method: 'GET',
        });
        const teamObj = await response.json();
        const sumOfPrizePool = getSumOfPrizePool(teamObj.participatedTournaments);

        return {teamObj, sumOfPrizePool};
    } catch (error) {
        console.error('Error fetching data:', error);
        document.getElementById('errorPopup').style.display = 'block';
        setTimeout(() => {
            document.getElementById('errorPopup').style.display = 'none';
        }, 3000);
    }
}

function getSumOfPrizePool(tournaments) {
    const tournamentCount = tournaments.length;

    console.log(`Team has participated in ${tournamentCount} tournaments.`);
    let finalSum = 0;

    tournaments.forEach(tournament => {
        finalSum += tournament.prizePool;
    });

    console.log(`Total Prize Pool: ${finalSum}`);
    return finalSum;
}


document.getElementById('addTeamToTournament').addEventListener('submit', async function (event) {
    event.preventDefault();

    const teamId = document.getElementById('teamId').value;
    const tournamentId = parseFloat(document.getElementById('tournamentId').value);


    const {teamObj, sumOfPrizePool} = await getTeamInfo(teamId);


    console.log(teamObj.teamName, " sa zucastnil turnajov s prizepoolom dokopy ", sumOfPrizePool);

    if (sumOfPrizePool >= 10000000) {
        console.log("Moc velky prizepool");
        // Display error popup
        document.getElementById('errorPopup').style.display = 'block';
        setTimeout(() => {
            document.getElementById('errorPopup').style.display = 'none';
        }, 3000);
    } else {
        addTeamToTournament(teamId, tournamentId);
    }

    this.reset();
});


async function addTeamToTournament(teamId, tournamentId) {
    try {
        const response = await fetch(`http://localhost:8080/team/tournament/${teamId}/${tournamentId}`, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json',
            },
        });

        if (response.ok) {
            console.log('Team updated successfully');
            document.getElementById('successPopup').style.display = 'block';
            setTimeout(() => {
                document.getElementById('successPopup').style.display = 'none';
            }, 3000);
        } else {
            console.error('Error updating team:', response.status);
            document.getElementById('errorPopup').style.display = 'block';
            setTimeout(() => {
                document.getElementById('errorPopup').style.display = 'none';
            }, 3000);
        }
    } catch (error) {
        console.error('Error fetching data:', error);
        document.getElementById('errorPopup').style.display = 'block';
        setTimeout(() => {
            document.getElementById('errorPopup').style.display = 'none';
        }, 3000);
    }
}

async function addPlayerToTeam(playerId, teamId) {
    try {
        const response = await fetch(`http://localhost:8080/team/player/${teamId}/${playerId}`, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json',
            },
        });

        if (response.ok) {
            console.log('Team updated successfully');
            document.getElementById('successPopup').style.display = 'block';
            setTimeout(() => {
                document.getElementById('successPopup').style.display = 'none';
            }, 3000);
        } else {
            console.error('Error updating team:', response.status);
            document.getElementById('errorPopup').style.display = 'block';
            setTimeout(() => {
                document.getElementById('errorPopup').style.display = 'none';
            }, 3000);
        }
    } catch (error) {
        console.error('Error fetching data:', error);
        document.getElementById('errorPopup').style.display = 'block';
        setTimeout(() => {
            document.getElementById('errorPopup').style.display = 'none';
        }, 3000);
    }
}

document.getElementById('addPlayerToTeam').addEventListener('submit', async function (event) {
    event.preventDefault();

    const teamId = document.getElementById('addPlayerToTeamTeamId').value;
    const playerId = parseFloat(document.getElementById('addPlayerToTeamPlayerId').value);


    addPlayerToTeam(playerId,teamId);

    this.reset();
});

fetchPlayers();
fetchTeams();
fetchTournaments();
