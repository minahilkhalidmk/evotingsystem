/* ==========================================================================
   AURAVOTE - JAVASCRIPT STATE ENGINE & OOP ARCHITECTURE CONTROLLER
   ========================================================================== */

// --- STATE MANAGEMENT ---
const state = {
  currentElectionType: "National", // "National", "Regional", "Local"
  activeVoter: null, // Logged in User/Voter object
  voters: [
    { cnic: "35202-1234567-1", pass: "voter123", name: "Alice Johnson", hasVoted: false, votedFor: null },
    { cnic: "35202-7654321-2", pass: "voter123", name: "Bob Smith", hasVoted: false, votedFor: null },
    { cnic: "35202-9999999-3", pass: "voter123", name: "Charlie Brown", hasVoted: false, votedFor: null }
  ],
  admins: [
    { cnic: "11111-1111111-1", pass: "admin123", name: "System Administrator" }
  ],
  candidates: [
    { id: 101, name: "Dr. Eleanor Vance", party: "Progressive Front", votes: 412, manifesto: "Focusing on digital infrastructure, green energy initiatives, and open governance." },
    { id: 102, name: "Marcus Aurelius Sterling", party: "Unity Alliance", votes: 345, manifesto: "Promoting economic stability, fiscal transparency, and civic empowerment." },
    { id: 103, name: "Sophia Lin", party: "Green Tomorrow", votes: 210, manifesto: "Pioneering sustainable urban development and clean water access for all." },
    { id: 104, name: "David K. Miller", party: "Civic Liberty", votes: 125, manifesto: "Championing individual privacy, decentralization, and small business support." }
  ],
  votesLog: [
    { cnic: "35202-0000000-0", candidateId: 101, timestamp: "2026-09-01 18:30:00" },
    { cnic: "35202-1111111-0", candidateId: 102, timestamp: "2026-09-01 19:15:22" }
  ],
  callStackHistory: [
    "main() -> Instantiated EVotingSystem system;",
    "EVotingSystem::seedInitialData() -> Seeded 3 Voters & 4 Candidates into Heap memory;",
    "Current active election -> NationalElection : public Election"
  ]
};

let resultsChart = null;

// --- INITIALIZATION ---
document.addEventListener("DOMContentLoaded", () => {
  initParallaxEngine();
  renderCandidates();
  initResultsChart();
  updateFileSimDisplay();
  updateCallStackUI();
});

// --- PARALLAX & GLASS TILT ENGINE ---
function initParallaxEngine() {
  const orb1 = document.getElementById("orb1");
  const orb2 = document.getElementById("orb2");
  const orb3 = document.getElementById("orb3");
  const heroStage = document.getElementById("heroStage");
  const frontGlassCard = document.getElementById("frontGlassCard");

  // Scroll Parallax Effect
  window.addEventListener("scroll", () => {
    const scrolled = window.scrollY;
    
    if (orb1) orb1.style.transform = `translate3d(0, ${scrolled * 0.22}px, 0)`;
    if (orb2) orb2.style.transform = `translate3d(0, ${scrolled * -0.16}px, 0)`;
    if (orb3) orb3.style.transform = `translate3d(0, ${scrolled * 0.1}px, 0)`;
  });

  // Mouse Move 3D Glass Tilt Effect
  if (heroStage && frontGlassCard) {
    heroStage.addEventListener("mousemove", (e) => {
      const rect = heroStage.getBoundingClientRect();
      const x = e.clientX - rect.left - rect.width / 2;
      const y = e.clientY - rect.top - rect.height / 2;

      const rotateX = (y / rect.height) * -18;
      const rotateY = (x / rect.width) * 18;

      frontGlassCard.style.transform = `perspective(1000px) rotateX(${rotateX}deg) rotateY(${rotateY}deg) translateZ(16px)`;
    });

    heroStage.addEventListener("mouseleave", () => {
      frontGlassCard.style.transform = `perspective(1000px) rotateX(0deg) rotateY(0deg) translateZ(0px)`;
    });
  }
}

// --- TAB SWITCHING LOGIC ---
function switchTab(tabId) {
  document.querySelectorAll(".form-glass-container").forEach(el => el.style.display = "none");
  document.querySelectorAll(".tab-btn").forEach(btn => btn.classList.remove("active"));
  
  const targetForm = document.getElementById(tabId);
  if (targetForm) targetForm.style.display = "block";

  const activeBtn = Array.from(document.querySelectorAll(".tab-btn")).find(b => b.getAttribute("onclick") && b.getAttribute("onclick").includes(tabId));
  if (activeBtn) activeBtn.classList.add("active");
}

function switchUmlTab(tabId) {
  document.getElementById("diagramTab").style.display = "none";
  document.getElementById("stackTab").style.display = "none";
  document.getElementById("codeTab").style.display = "none";

  const target = document.getElementById(tabId);
  if (target) target.style.display = "block";

  const buttons = document.querySelectorAll("#uml .tab-btn");
  buttons.forEach(btn => btn.classList.remove("active"));

  const activeBtn = Array.from(buttons).find(b => b.getAttribute("onclick").includes(tabId));
  if (activeBtn) activeBtn.classList.add("active");
}

// --- OOP PILLAR HIGHLIGHT ---
function highlightOOPConcept(concept) {
  let msg = "";
  if (concept === "encapsulation") {
    msg = "[ENCAPSULATION IN C++]\n- Private variables: cnic, password, voteCount.\n- Public getters & setters protect data integrity.\n- Prevents unauthorized modification of voter records.";
  } else if (concept === "inheritance") {
    msg = "[INHERITANCE IN C++]\n- Base Class: User -> Derived: Voter, Admin.\n- Base Class: Election -> Derived: LocalElection, RegionalElection, NationalElection.\n- Promotes code reuse and clean class hierarchy.";
  } else if (concept === "polymorphism") {
    msg = "[POLYMORPHISM IN C++]\n- Virtual functions: virtual string getRole() const override.\n- Dynamic binding at runtime allows treating Voter & Admin pointers as generic User*.";
  } else if (concept === "abstraction") {
    msg = "[ABSTRACTION IN C++]\n- Pure virtual function: virtual string getRole() = 0;\n- User is an Abstract Base Class that cannot be instantiated directly.";
  }
  alert(msg);
}

// --- VOTER AUTHENTICATION ---
function handleVoterLogin(e) {
  e.preventDefault();
  const cnic = document.getElementById("loginCnic").value.trim();
  const pass = document.getElementById("loginPass").value.trim();

  const voter = state.voters.find(v => v.cnic === cnic && v.pass === pass);

  if (voter) {
    state.activeVoter = voter;
    logCallStack(`User::authenticate("${cnic}") -> SUCCESS | Role: Voter | Object: ${voter.name}`);
    alert(`[AUTHENTICATED] Welcome ${voter.name}!\nC++ Method Executed: User::authenticate() & Voter::getRole()`);
    document.getElementById("ballot").scrollIntoView({ behavior: "smooth" });
    renderCandidates();
  } else {
    logCallStack(`User::authenticate("${cnic}") -> FAILED (Invalid credentials)`);
    alert("[ERROR] Invalid CNIC or Password. Try clicking 'Demo Voter Object' at top header!");
  }
}

function handleVoterRegister(e) {
  e.preventDefault();
  const name = document.getElementById("regName").value.trim();
  const cnic = document.getElementById("regCnic").value.trim();
  const pass = document.getElementById("regPass").value.trim();

  if (state.voters.some(v => v.cnic === cnic)) {
    alert("[ERROR] CNIC already registered!");
    return;
  }

  const newVoter = { cnic, pass, name, hasVoted: false, votedFor: null };
  state.voters.push(newVoter);
  state.activeVoter = newVoter;

  logCallStack(`new Voter("${cnic}", "${pass}", "${name}") -> Memory allocated on Heap`);
  alert(`[OBJECT INSTANTIATED] Voter ${name} added to memory & users.txt!`);
  
  updateFileSimDisplay();
  switchTab("loginTab");
  renderCandidates();
  document.getElementById("ballot").scrollIntoView({ behavior: "smooth" });
}

function handleAdminLogin(e) {
  e.preventDefault();
  const cnic = document.getElementById("adminCnic").value.trim();
  const pass = document.getElementById("adminPass").value.trim();

  const admin = state.admins.find(a => a.cnic === cnic && a.pass === pass);
  if (admin) {
    logCallStack(`Admin::authenticate("${cnic}") -> SUCCESS | Role: Admin`);
    alert(`[ADMIN GRANTED] Welcome ${admin.name}\nExecuting Admin::adminMenu()`);
    document.getElementById("admin").scrollIntoView({ behavior: "smooth" });
  } else {
    alert("[ERROR] Invalid Admin Credentials. Default: 11111-1111111-1 / admin123");
  }
}

function quickLoginDemo() {
  state.activeVoter = state.voters[0];
  logCallStack(`Demo Session Activated -> Pointer: User* activeVoter = &voters[0] (${state.voters[0].name})`);
  alert(`[DEMO USER OBJECT] Logged in as ${state.voters[0].name} (${state.voters[0].cnic})`);
  document.getElementById("ballot").scrollIntoView({ behavior: "smooth" });
  renderCandidates();
}

// --- CANDIDATE GRID & VOTING MECHANICS ---
function renderCandidates() {
  const container = document.getElementById("candidateGrid");
  if (!container) return;

  const totalVotes = state.candidates.reduce((sum, c) => sum + c.votes, 0);

  container.innerHTML = state.candidates.map(cand => {
    const pct = totalVotes > 0 ? ((cand.votes / totalVotes) * 100).toFixed(1) : 0;
    const isVotedByActiveUser = state.activeVoter && state.activeVoter.votedFor === cand.id;

    return `
      <div class="candidate-glass-card">
        <span class="oop-class-tag">Candidate ID: ${cand.id}</span>
        <div>
          <div class="candidate-header">
            <div class="candidate-avatar">${getInitials(cand.name)}</div>
            <div class="candidate-info">
              <h3>${cand.name}</h3>
              <div class="candidate-party">${cand.party}</div>
            </div>
          </div>
          <div class="candidate-manifesto">
            "${cand.manifesto}"
          </div>
        </div>

        <div>
          <div style="display: flex; justify-content: space-between; font-size: 0.82rem; font-weight: 600; margin-bottom: 6px; color: var(--mocha-dark);">
            <span>Vote Share (Candidate::voteCount)</span>
            <span>${cand.votes} votes (${pct}%)</span>
          </div>
          <div class="vote-progress-bar">
            <div class="vote-progress-fill" style="width: ${pct}%;"></div>
          </div>

          <button class="btn-glass ${isVotedByActiveUser ? 'btn-gold' : 'btn-primary'}" 
                  style="width: 100%; justify-content: center;" 
                  onclick="castVote(${cand.id})">
            ${isVotedByActiveUser ? '✓ Vote Registered' : 'Invoke Candidate::incrementVote()'}
          </button>
        </div>
      </div>
    `;
  }).join('');
}

function getInitials(name) {
  return name.split(' ').map(n => n[0]).join('').substring(0, 2).toUpperCase();
}

function castVote(candidateId) {
  if (!state.activeVoter) {
    alert("Please log in or click 'Demo Voter Object' first to cast your ballot.");
    document.getElementById("portal").scrollIntoView({ behavior: "smooth" });
    return;
  }

  if (state.activeVoter.hasVoted) {
    alert(`[WARNING] Single-Vote Guard: User ${state.activeVoter.name} has already voted in this session!`);
    return;
  }

  const candidate = state.candidates.find(c => c.id === candidateId);
  if (!candidate) return;

  // Process Vote & Invoke Method
  candidate.votes++;
  state.activeVoter.hasVoted = true;
  state.activeVoter.votedFor = candidateId;

  logCallStack(`Candidate::incrementVote() -> Candidate[ID:${candidateId}, Name:${candidate.name}] votes = ${candidate.votes}`);

  // Record Vote Log
  state.votesLog.push({
    cnic: state.activeVoter.cnic,
    candidateId: candidateId,
    timestamp: new Date().toISOString().replace('T', ' ').substring(0, 19)
  });

  // UI Updates
  renderCandidates();
  updateResultsChart();
  updateFileSimDisplay();

  // Show Digital Cryptographic Receipt
  showReceiptModal(candidate);
}

// --- CALL STACK TRACER UI ---
function logCallStack(entry) {
  const time = new Date().toLocaleTimeString();
  state.callStackHistory.unshift(`[${time}] ${entry}`);
  updateCallStackUI();
}

function updateCallStackUI() {
  const container = document.getElementById("callStackLog");
  if (!container) return;

  let content = `<span style="color: var(--champagne-gold);">[CALL STACK TRACER - RUNTIME MEMORY DISPATCH]</span><br><br>`;
  state.callStackHistory.slice(0, 8).forEach(item => {
    content += `&gt; ${item}<br>`;
  });

  container.innerHTML = content;
}

// --- DIGITAL RECEIPT MODAL ---
function showReceiptModal(candidate) {
  const modal = document.getElementById("receiptModal");
  const modalHash = document.getElementById("modalHash");
  const modalCnic = document.getElementById("modalCnic");
  const modalCandidate = document.getElementById("modalCandidate");
  const modalTime = document.getElementById("modalTime");

  const simulatedHash = "0x" + Array.from({length: 24}, () => Math.floor(Math.random()*16).toString(16)).join('');

  modalHash.innerText = "BALLOT HASH: " + simulatedHash;
  modalCnic.innerText = state.activeVoter.cnic;
  modalCandidate.innerText = `${candidate.name} (${candidate.party})`;
  modalTime.innerText = new Date().toLocaleString();

  modal.classList.add("active");
}

function closeReceiptModal() {
  document.getElementById("receiptModal").classList.remove("active");
}

// --- LIVE RESULTS CHART.JS ---
function initResultsChart() {
  const ctx = document.getElementById("resultsCanvas");
  if (!ctx) return;

  const labels = state.candidates.map(c => c.name);
  const data = state.candidates.map(c => c.votes);

  resultsChart = new Chart(ctx, {
    type: 'bar',
    data: {
      labels: labels,
      datasets: [{
        label: 'Votes Cast',
        data: data,
        backgroundColor: [
          'rgba(198, 139, 89, 0.75)',
          'rgba(212, 175, 55, 0.75)',
          'rgba(227, 202, 165, 0.85)',
          'rgba(213, 189, 175, 0.85)'
        ],
        borderColor: [
          '#C68B59',
          '#D4AF37',
          '#E3CAA5',
          '#D5BDAF'
        ],
        borderWidth: 2,
        borderRadius: 10
      }]
    },
    options: {
      responsive: true,
      maintainAspectRatio: false,
      plugins: {
        legend: { display: false }
      },
      scales: {
        y: {
          beginAtZero: true,
          grid: { color: 'rgba(61, 44, 46, 0.06)' },
          ticks: { color: '#3D2C2E', font: { family: 'Plus Jakarta Sans', weight: '600' } }
        },
        x: {
          grid: { display: false },
          ticks: { color: '#3D2C2E', font: { family: 'Plus Jakarta Sans', weight: '600' } }
        }
      }
    }
  });

  updateResultsSummaryList();
}

function updateResultsChart() {
  if (!resultsChart) return;
  resultsChart.data.labels = state.candidates.map(c => c.name);
  resultsChart.data.datasets[0].data = state.candidates.map(c => c.votes);
  resultsChart.update();
  updateResultsSummaryList();
}

function updateResultsSummaryList() {
  const summaryContainer = document.getElementById("resultsSummaryList");
  if (!summaryContainer) return;

  const total = state.candidates.reduce((acc, c) => acc + c.votes, 0);

  summaryContainer.innerHTML = state.candidates.map(c => {
    const pct = total > 0 ? ((c.votes / total) * 100).toFixed(1) : 0;
    return `
      <div style="display: flex; justify-content: space-between; align-items: center; padding: 10px 14px; background: rgba(255,255,255,0.45); border-radius: 12px; border: 1px solid rgba(255,255,255,0.6);">
        <div>
          <strong style="color: var(--mocha-dark); font-size: 0.9rem; display: block;">${c.name}</strong>
          <span style="font-size: 0.76rem; color: var(--slate-rose);">${c.party}</span>
        </div>
        <div style="text-align: right;">
          <strong style="color: var(--terracotta); font-size: 0.95rem;">${c.votes} votes</strong>
          <span style="display: block; font-size: 0.76rem; color: var(--mocha-dark); font-weight: 700;">${pct}%</span>
        </div>
      </div>
    `;
  }).join('');
}

// --- ADMIN ELECTION CONTROL ---
function changeElectionType(type) {
  state.currentElectionType = type;
  const title = document.getElementById("currentElectionTitle");

  if (title) title.innerText = `Candidate Objects (${type}Election : public Election)`;

  logCallStack(`Polymorphic Switch: delete currentElection; currentElection = new ${type}Election();`);
  alert(`[POLYMORPHIC SWITCH] Instantiated derived class ${type}Election : public Election`);
}

function handleAddCandidate(e) {
  e.preventDefault();
  const name = document.getElementById("newCandName").value.trim();
  const party = document.getElementById("newCandParty").value.trim();

  const newId = 100 + state.candidates.length + 1;
  state.candidates.push({
    id: newId,
    name: name,
    party: party,
    votes: 0,
    manifesto: "Dedicated to transparent community leadership and regional development."
  });

  document.getElementById("newCandName").value = "";
  document.getElementById("newCandParty").value = "";

  logCallStack(`Election::addCandidate(Candidate(${newId}, "${name}", "${party}")) -> Vector push_back()`);
  renderCandidates();
  updateResultsChart();
  alert(`[SUCCESS] Candidate object ${name} added to election vector!`);
}

// --- FILE SYSTEM SIMULATOR DISPLAY ---
function updateFileSimDisplay() {
  const container = document.getElementById("fileSystemSim");
  if (!container) return;

  let content = `<span style="color: #D4AF37;">// === users.txt (File Persistence Stream) ===</span>\n`;
  state.voters.forEach(v => {
    content += `Voter,${v.cnic},${v.name},${v.pass}\n`;
  });

  content += `\n<span style="color: #D4AF37;">// === votes.txt (File Persistence Stream) ===</span>\n`;
  state.votesLog.forEach(vl => {
    content += `VoteRecord,${vl.cnic},CandID:${vl.candidateId},${vl.timestamp}\n`;
  });

  container.innerHTML = content.replace(/\n/g, "<br>");
}
